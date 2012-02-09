#include "Utils.h"
#include <GLES/gl.h>

void drawDebugRectangle(const Vector2& pos, UInt32 width, UInt32 height, bool forSprite)
{
    GLfixed vertices[] =
    {
        pos.x(), pos.y(),
        pos.x(), pos.y() + height - 1,
        pos.x() + width - 1, pos.y() + height - 1,
        pos.x() + width - 1, pos.y()
    };

    glDisable(GL_BLEND);
    glDisable(GL_TEXTURE_2D);

    glEnableClientState(GL_VERTEX_ARRAY);

    if (forSprite)
    {
        glColor4f(0.0f, 1.0f, 0.0f, 1.0f);
    }
    else
    {
        glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
    }

    glVertexPointer(2, GL_FIXED, 0, &vertices[0]);

    glDrawArrays(GL_LINE_LOOP, 0, sizeof(vertices) / (2 * sizeof(vertices[0])));

    glDisableClientState(GL_VERTEX_ARRAY);

    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
}

bool detectLineCircleCollision( const Vector2& p1,
                                const Vector2& p2,
                                const Vector2& c1,
                                const Vector2& c2,
                                float radius,
                                Vector2& newC )
{
    float d1 = linePointDistance(p1, p2, c1);

    if (d1 < -radius)
    {
        /*
         * We've already passed the line, no collision.
         */

        return false;
    }

    float d2 = linePointDistance(p1, p2, c2);

    float d2d1 = d2 - d1;

    if (d2d1 >= 0.0f)
    {
        /*
         * Circle is not floating towards the normal, no collision.
         */

        return false;
    }

    /*
     * Solve the equation: radius = d1 + (d2 - d1) * t.
     */

    float t = (radius - d1) / d2d1;

    if (t > 1.0f)
    {
        /*
         * The solution is after our trajectory end, no collision.
         */

        return false;
    }

    /*
     * We have/had the collision, calculate the collision point.
     */

    newC = c1 + (c2 - c1) * t;

    return true;
}

float linePointDistance( const Vector2& p1,
                         const Vector2& p2,
                         const Vector2& c )
{
    Vector2 tmp = (p2 - p1).clockwiseNormal();

    tmp.normalize();

    /*
     * 'tmp' is a unit normal of "p1->p2", thus, dot product of "p1->c" and "tmp"
     * is the distance between "c" and "p1->p2"
     */

    return tmp.dot(c - p1);
}

bool detectLineSegmentCircleCollision( const Vector2& p1,
                                       const Vector2& p2,
                                       const Vector2& c1,
                                       const Vector2& c2,
                                       float radius,
                                       Vector2& newC )
{
    if (!detectLineCircleCollision( p1,
                                    p2,
                                    c1,
                                    c2,
                                    radius,
                                    newC ))
    {
        /*
         * If there's no collision with line there can be no collision with line
         * segment.
         */

        return false;
    }

    Vector2 tmp = (p2 - p1);

    float tmpLength2 = tmp.length2();

    if (tmpLength2 == 0.0f)
    {
        /*
         * Just in case.
         */

        return false;
    }

    /*
     * 't' is the position of 'newC' projection on line "p1->p2", it's
     * < 0.0 when 'newC' is projected before 'p1', > 1.0 when 'newC'
     * is projected after 'p2', otherwise the projection is inside the line
     * segment.
     */

    float t = ((newC - p1).dot(tmp)) / tmpLength2;

    tmp = (c2 - c1);

    tmp.normalize();

    float newCC1ProjLen = (c1 - newC).dot(tmp);

    Vector2 p;
    float d = 0.0f;
    bool onSegment = false;

    if ((t > 0.0f) && (t < 1.0f))
    {
        /*
         * The projection is inside the line segment, this means
         * that the 'newC's tangent point is on the line segment.
         */

        onSegment = true;

        if (newCC1ProjLen <= 0.0f)
        {
            /*
             * 'c1' is before 'newC', there's a collision
             */

            return true;
        }

        /*
         * 'c1' is after 'newC', we must decide if it's tangent to "p1->p2".
         */

        d = linePointDistance(newC, c2, p1);

        if (d < 0.0f)
        {
            d = linePointDistance(newC, c2, p2);

            if (d > 0.0f)
            {
                /*
                 * It's tangent, collision is present.
                 */

                return true;
            }
            else
            {
                /*
                 * Not tangent and floats in 'p2' direction.
                 */

                d = fabs(d);
                p = p2;
            }
        }
        else
        {
            /*
             * Not tangent and floats in 'p1' direction.
             */

            p = p1;
        }
    }
    else
    {
        if (t <= 0.0f)
        {
            p = p1;
        }
        else
        {
            p = p2;
        }

        /*
         * 'p' is the endpoint of the line segment closest to 'newC'.
         * Find absolute distance between "newC->c2" and "p".
         */

        d = fabs(linePointDistance(newC, c2, p));

        if (d > radius)
        {
            /*
             * The distance is greater than radius, there's no way for collision,
             * we're done.
             */

            return false;
        }
    }

    /*
     * Here's what we have:
     *
     * * newC
     *  \
     *    \
     *      \ offset
     *      | \
     *radius|  /\
     *      | /d  \
     *      |/      \
     * -----*         \
     *       p          \
     *                   * c2
     *
     * So, in order to get the correct 'newC' we must first calculate 'offset'
     * and move 'newC' appropriately.
     */

    float offset = sqrt(radius * radius - d * d);

    float newCPProjLen = (p - newC).dot(tmp);

    if (newCC1ProjLen > (newCPProjLen + offset))
    {
        /*
         * We've already flew over the endpoint, no collision.
         */

        return false;
    }

    if (onSegment)
    {
        /*
         * If we're on segment there's a collision and 'newC' is already correct.
         */
    }
    else
    {
        /*
         * If we're not on segment we might be floating in air, unless 'c2' is touching
         * the endpoint.
         */

        float newCC2ProjLen = (c2 - newC).dot(tmp);

        if (newCC2ProjLen < (newCPProjLen - offset))
        {
            /*
             * 'c2' isn't touching the endpoint, we're in air.
             */

            return false;
        }

        /*
         * Fixup for 'newC', it should touch the endpoint.
         */

        tmp *= (newCPProjLen - offset);

        newC += tmp;
    }

    return true;
}

Vector2 generateLineCircleCollisionResponse( const Vector2& p1,
                                             const Vector2& p2,
                                             const Vector2& c1,
                                             const Vector2& c2,
                                             const Vector2& newC,
                                             Vector2& normalizedDirection )
{
    Vector2 tmp2 = (c2 - c1);
    float c1c2Length = tmp2.normalize();

    normalizedDirection = (p2 - p1).reflect(tmp2);

    return (newC + (normalizedDirection * c1c2Length));
}

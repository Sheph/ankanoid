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
    float d2 = linePointDistance(p1, p2, c2);

    float d2d1 = d2 - d1;

    if (d2d1 == 0.0f)
    {
        /*
         * Floats can be divided by 0 safely, but just in case.
         */

        return false;
    }

    /*
     * Solve the equation: radius = d1 + (d2 - d1) * t.
     */

    float t = (radius - d1) / d2d1;

    if ( (t < 0.0f) || (t > 1.0f) )
    {
        /*
         * The solution is not within our trajectory, no collision.
         */

        return false;
    }

    /*
     * We have the collision, calculate the collision point.
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
                                       Vector2& newC,
                                       bool& collisionIsOnEndpoint )
{
    collisionIsOnEndpoint = false;

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

    if ((t > 0.0f) && (t < 1.0f))
    {
        /*
         * The projection is inside the line segment, this means
         * that the 'newC's tangent point is on the line segment,
         * we're done.
         */

        return true;
    }

    Vector2 p;

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

    float d = fabs(linePointDistance(newC, c2, p));

    if (d > radius)
    {
        /*
         * The distance is greater than radius, there's no way for collision,
         * we're done.
         */

        return false;
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

    tmp = (c2 - newC);

    tmp.normalize();

    tmp *= ((p - newC).dot(tmp) - offset);

    newC += tmp;

    collisionIsOnEndpoint = true;

    return true;
}

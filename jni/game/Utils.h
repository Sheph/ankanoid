#ifndef _UTILS_H_
#define _UTILS_H_

#include "Types.h"
#include "Vector2.h"

void drawDebugRectangle(const Vector2& pos, UInt32 width, UInt32 height, bool forSprite);

/*
 * Detects line <-> circle collision where circle is moving from point 'c1' to 'c2'.
 * This method is line normal aware, collision is only detected if "c1->c2" is facing the normal.
 * Returns true if collision was detected, it'll also set 'newC' to the suggested new value
 * instead of 'c2'.
 */
bool detectLineCircleCollision( const Vector2& p1,
                                const Vector2& p2,
                                const Vector2& c1,
                                const Vector2& c2,
                                float radius,
                                Vector2& newC );

/*
 * This method is line normal aware, if 'c' is facing the normal then result is
 * positive, else it's negative
 */
float linePointDistance( const Vector2& p1,
                         const Vector2& p2,
                         const Vector2& c );

/*
 * Same as 'detectLineCircleCollision', but for line segment.
 */
bool detectLineSegmentCircleCollision( const Vector2& p1,
                                       const Vector2& p2,
                                       const Vector2& c1,
                                       const Vector2& c2,
                                       float radius,
                                       Vector2& newC );

/*
 * Reflects the circle off the line "p1->p2" keeping the distance length
 * "c1->newC" + "newC->result" equal to "c1->c2".
 */
Vector2 generateLineCircleCollisionResponse( const Vector2& p1,
                                             const Vector2& p2,
                                             const Vector2& c1,
                                             const Vector2& c2,
                                             const Vector2& newC,
                                             Vector2& normalizedDirection );

#endif

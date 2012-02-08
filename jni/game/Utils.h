#ifndef _UTILS_H_
#define _UTILS_H_

#include "Types.h"
#include "Vector2.h"

void drawDebugRectangle(const Vector2& pos, UInt32 width, UInt32 height, bool forSprite);

/*
 * Detects line <-> circle collision where circle is moving from point 'c1' to 'c2'.
 * This method is line normal aware, collision is only detected if 'c1' is facing the normal.
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
 * 'collisionIsOnEndpoint' will be set if the collision was detected on
 * one of the line segment's endpoints.
 */
bool detectLineSegmentCircleCollision( const Vector2& p1,
                                       const Vector2& p2,
                                       const Vector2& c1,
                                       const Vector2& c2,
                                       float radius,
                                       Vector2& newC,
                                       bool& collisionIsOnEndpoint );

#endif

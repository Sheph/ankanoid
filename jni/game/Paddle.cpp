#include "Paddle.h"
#include "Utils.h"

void Paddle::render(UInt32 deltaMs, bool debug)
{
    sprite_.render(deltaMs, debug);

    if (debug)
    {
        drawDebugRectangle(sprite_.pos() + boundOffset_, boundWidth_, boundHeight_, false);
    }
}

Vector2 Paddle::boundAbsPos() const
{
    return sprite().pos() + boundOffset();
}

Vector2 Paddle::boundAbsCenter() const
{
    Vector2 pos = boundAbsPos();

    return Vector2( pos.x() + (boundWidth() / 2),
                    pos.y() + (boundHeight() / 2) );
}

#include "Ball.h"
#include "Utils.h"

void Ball::render(UInt32 deltaMs, bool debug)
{
    sprite_.render(deltaMs, debug);

    if (debug)
    {
        Vector2 pos = sprite_.pos();

        pos += center_;

        pos -= Vector2(radius_, radius_);

        drawDebugRectangle(pos, radius_ * 2, radius_ * 2, false);
    }
}

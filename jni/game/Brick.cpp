#include "Brick.h"
#include "Utils.h"

void Brick::render(UInt32 deltaMs, bool debug)
{
    sprite_.render(deltaMs, debug);

    if (debug)
    {
        drawDebugRectangle(sprite_.pos() + boundOffset_, boundWidth_, boundHeight_, false);
    }
}

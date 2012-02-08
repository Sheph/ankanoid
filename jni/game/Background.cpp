#include "Background.h"
#include "Utils.h"

void Background::render(UInt32 deltaMs, bool debug)
{
    sprite_.render(deltaMs);

    if (debug)
    {
        Vector2 pos = sprite_.pos();

        pos += Vector2(left_, -1);

        drawDebugRectangle(pos, (right_ - left_), sprite_.height() + 1, false);
    }
}

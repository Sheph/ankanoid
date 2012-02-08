#include "Vector2.h"

void Vector2::rotateClockwise(float deg)
{
    float radians = (deg * M_PI) / 180;

    x_ = (x_ * cos(radians)) + (y_ * sin(radians));
    y_ = (y_ * cos(radians)) - (x_ * sin(radians));
}

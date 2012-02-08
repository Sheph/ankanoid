#include "Vector2.h"

void Vector2::clockwiseRotate(float deg)
{
    float radians = (deg * M_PI) / 180;

    x_ = (x_ * cos(radians)) + (y_ * sin(radians));
    y_ = (y_ * cos(radians)) - (x_ * sin(radians));
}

Vector2 Vector2::clockwiseNormal() const
{
    return Vector2(y_, -x_);
}

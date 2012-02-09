#include "Vector2.h"

void Vector2::clockwiseRotate(float deg)
{
    float radians = (deg * M_PI) / 180;

    float x = x_;
    float y = y_;

    x_ = (x * cos(radians)) + (y * sin(radians));
    y_ = (y * cos(radians)) - (x * sin(radians));
}

Vector2 Vector2::clockwiseNormal() const
{
    return Vector2(y_, -x_);
}

Vector2 Vector2::reflect(const Vector2& other) const
{
    Vector2 tmp = clockwiseNormal();

    tmp.normalize();

    tmp *= other.dot(tmp) * 2;

    return other - tmp;
}

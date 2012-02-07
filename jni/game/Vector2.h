#ifndef _VECTOR2_H_
#define _VECTOR2_H_

#include "Types.h"

class Vector2
{
public:
    Vector2()
    : x_(0),
      y_(0)
    {
    }

    Vector2(float x, float y)
    : x_(x),
      y_(y)
    {
    }

    Vector2& operator+=(const Vector2& other)
    {
        x_ += other.x_;
        y_ += other.y_;

        return *this;
    }

    Vector2& operator-=(const Vector2& other)
    {
        x_ -= other.x_;
        y_ -= other.y_;

        return *this;
    }

    Vector2 operator+(const Vector2& other) const
    {
        Vector2 tmp = *this;

        tmp += other;

        return tmp;
    }

    Vector2 operator-(const Vector2& other) const
    {
        Vector2 tmp = *this;

        tmp -= other;

        return tmp;
    }

    Vector2 operator-() const
    {
        return Vector2(-x_, -y_);
    }

    float x() const { return x_; }

    float y() const { return y_; }

private:
    float x_;
    float y_;
};

#endif

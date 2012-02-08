#ifndef _VECTOR2_H_
#define _VECTOR2_H_

#include "Types.h"
#include <math.h>

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

    Vector2& operator*=(float mag)
    {
        x_ *= mag;
        y_ *= mag;

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

    Vector2 operator*(float mag) const
    {
        Vector2 tmp = *this;

        tmp *= mag;

        return tmp;
    }

    Vector2 operator-() const
    {
        return Vector2(-x_, -y_);
    }

    float length() const
    {
        return sqrt(length2());
    }

    float length2() const
    {
        return (x_ * x_) + (y_ * y_);
    }

    float normalize()
    {
        float mag = length();

        if (mag != 0.0f)
        {
            x_ /= mag;
            y_ /= mag;
        }

        return mag;
    }

    float dot(const Vector2& other)
    {
        return (x_ * other.x_) + (y_ * other.y_);
    }

    void clockwiseRotate(float deg);

    Vector2 clockwiseNormal() const;

    inline float x() const { return x_; }

    inline float y() const { return y_; }

    inline void setX(float x) { x_ = x; }

    inline void setY(float y) { y_ = y; }

private:
    float x_;
    float y_;
};

#endif

#ifndef _BALL_H_
#define _BALL_H_

#include "Types.h"
#include "Sprite.h"
#include "Vector2.h"

class Ball
{
public:
    Ball()
    : radius_(0)
    {
    }

    Ball( const Sprite& sprite,
          const Vector2& center,
          UInt32 radius )
    : sprite_(sprite),
      center_(center),
      radius_(radius)
    {
    }

    ~Ball()
    {
    }

    void render(UInt32 deltaMs, bool debug = false);

    inline Sprite& sprite() { return sprite_; }

    inline const Vector2& center() const { return center_; }

    inline UInt32 radius() const { return radius_; }

private:
    Sprite sprite_;
    Vector2 center_;
    UInt32 radius_;
};

#endif

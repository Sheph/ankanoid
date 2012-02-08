#ifndef _BALL_H_
#define _BALL_H_

#include "Types.h"
#include "Sprite.h"
#include "Vector2.h"

class Ball
{
public:
    Ball()
    {
    }

    explicit Ball(const Sprite& sprite)
    : sprite_(sprite)
    {
    }

    ~Ball()
    {
    }

    void render(UInt32 deltaMs, bool debug = false);

    inline Sprite& sprite() { return sprite_; }

    inline Vector2& speed() { return speed_; }

private:
    Sprite sprite_;
    Vector2 speed_;
};

#endif

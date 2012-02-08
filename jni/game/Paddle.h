#ifndef _PADDLE_H_
#define _PADDLE_H_

#include "Types.h"
#include "Sprite.h"
#include "Vector2.h"

class Paddle
{
public:
    Paddle()
    : boundWidth_(0),
      boundHeight_(0)
    {
    }

    Paddle( const Sprite& sprite,
            const Vector2& boundOffset,
            UInt32 boundWidth,
            UInt32 boundHeight )
    : sprite_(sprite),
      boundOffset_(boundOffset),
      boundWidth_(boundWidth),
      boundHeight_(boundHeight)
    {
    }

    ~Paddle()
    {
    }

    void render(UInt32 deltaMs, bool debug = false);

    inline Sprite& sprite() { return sprite_; }

    inline const Vector2& boundOffset() const { return boundOffset_; }

    inline UInt32 boundWidth() const { return boundWidth_; }

    inline UInt32 boundHeight() const { return boundHeight_; }

    inline Vector2& speed() { return speed_; }

private:
    Sprite sprite_;
    Vector2 boundOffset_;
    UInt32 boundWidth_;
    UInt32 boundHeight_;
    Vector2 speed_;

};

#endif

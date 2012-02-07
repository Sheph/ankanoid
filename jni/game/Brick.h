#ifndef _BRICK_H_
#define _BRICK_H_

#include "Types.h"
#include "Sprite.h"
#include "Vector2.h"

class Brick
{
public:
    enum
    {
        AnimationDie = 1
    };

    Brick()
    : boundWidth_(0),
      boundHeight_(0)
    {
    }

    Brick( const Sprite& sprite,
           const Vector2& boundOffset,
           UInt32 boundWidth,
           UInt32 boundHeight )
    : sprite_(sprite),
      boundOffset_(boundOffset),
      boundWidth_(boundWidth),
      boundHeight_(boundHeight)
    {
    }

    ~Brick()
    {
    }

    inline Sprite& sprite() { return sprite_; }

    inline const Vector2& boundOffset() const { return boundOffset_; }

    inline UInt32 boundWidth() const { return boundWidth_; }

    inline UInt32 boundHeight() const { return boundHeight_; }

private:
    Sprite sprite_;
    Vector2 boundOffset_;
    UInt32 boundWidth_;
    UInt32 boundHeight_;
};

#endif

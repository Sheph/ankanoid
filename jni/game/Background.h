#ifndef _BACKGROUND_H_
#define _BACKGROUND_H_

#include "Types.h"
#include "Sprite.h"

class Background
{
public:
    Background()
    : left_(0),
      right_(0)
    {
    }

    Background( const Sprite& sprite,
                UInt32 left,
                UInt32 right )
    : sprite_(sprite),
      left_(left),
      right_(right)
    {
    }

    ~Background()
    {
    }

    void render(UInt32 deltaMs, bool debug = false);

    inline Sprite& sprite() { return sprite_; }

    inline UInt32 left() const { return left_; }

    inline UInt32 right() const { return right_; }

private:
    Sprite sprite_;
    UInt32 left_;
    UInt32 right_;
};

#endif

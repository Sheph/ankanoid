#ifndef _ANIMATIONFRAME_H_
#define _ANIMATIONFRAME_H_

#include "Types.h"

class AnimationFrame
{
public:
    AnimationFrame()
    : x_(0),
      y_(0),
      width_(0),
      height_(0),
      durationMs_(0)
    {
    }

    AnimationFrame( UInt32 x,
                    UInt32 y,
                    UInt32 width,
                    UInt32 height,
                    UInt32 durationMs )
    : x_(x),
      y_(y),
      width_(width),
      height_(height),
      durationMs_(durationMs)
    {
    }

    ~AnimationFrame()
    {
    }

    inline UInt32 x() const { return x_; }

    inline UInt32 y() const { return y_; }

    inline UInt32 width() const { return width_; }

    inline UInt32 height() const { return height_; }

    inline UInt32 durationMs() const { return durationMs_; }

private:
    UInt32 x_;
    UInt32 y_;
    UInt32 width_;
    UInt32 height_;
    UInt32 durationMs_;
};

#endif

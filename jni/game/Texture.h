#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include "Types.h"
#include <GLES/gl.h>

class Texture
{
public:
    Texture()
    : id_(0),
      width_(0),
      height_(0)
    {
    }

    Texture( GLuint id,
             UInt32 width,
             UInt32 height )
    : id_(id),
      width_(width),
      height_(height)
    {
    }

    ~Texture()
    {
    }

    inline GLuint id() const { return id_; }

    inline UInt32 width() const { return width_; }

    inline UInt32 height() const { return height_; }

private:
    GLuint id_;
    UInt32 width_;
    UInt32 height_;
};

#endif

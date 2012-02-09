#ifndef _ANIMATION_H_
#define _ANIMATION_H_

#include "Types.h"
#include "Texture.h"
#include "AnimationFrame.h"
#include "Vector2.h"
#include <map>

class Animation
{
public:
    Animation(const TexturePtr& texture, bool loop);
    ~Animation();

    void addFrame(const AnimationFrame& frame);

    void render(UInt32 timeMs, const Vector2& pos, UInt32 width, UInt32 height) const;

    bool finished(UInt32 timeMs) const;

    UInt32 durationMs() const;

private:
    typedef std::map<UInt32, AnimationFrame> AnimationFrameMap;

    void renderFrame( const AnimationFrame& frame,
                      const Vector2& pos,
                      UInt32 width,
                      UInt32 height ) const;

    TexturePtr texture_;
    bool loop_;
    AnimationFrameMap frames_;
};

#endif

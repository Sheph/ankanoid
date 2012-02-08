#include "Sprite.h"
#include "Utils.h"
#include <assert.h>

Sprite::Sprite()
: width_(0),
  height_(0),
  curAnimationId_(-1),
  curAnimationTimeMs_(0)
{
}

Sprite::Sprite( UInt32 width,
                UInt32 height )
: width_(width),
  height_(height),
  curAnimationId_(-1),
  curAnimationTimeMs_(0)
{
}

Sprite::~Sprite()
{
}

void Sprite::addAnimation(int id, const Animation& animation)
{
    bool res = animations_.insert(std::make_pair(id, animation)).second;
    assert(res);
}

void Sprite::render(UInt32 deltaMs, bool debug)
{
    AnimationMap::const_iterator it = animations_.find(curAnimationId_);

    if (it == animations_.end())
    {
        return;
    }

    curAnimationTimeMs_ += deltaMs;

    it->second.render(curAnimationTimeMs_, pos_, width_, height_);

    if (debug)
    {
        drawDebugRectangle(pos_, width_, height_, true);
    }
}

void Sprite::startAnimation(int id)
{
    curAnimationId_ = id;
    curAnimationTimeMs_ = 0;
}

bool Sprite::animationFinished() const
{
    AnimationMap::const_iterator it = animations_.find(curAnimationId_);

    if (it == animations_.end())
    {
        return true;
    }

    return it->second.finished(curAnimationTimeMs_);
}

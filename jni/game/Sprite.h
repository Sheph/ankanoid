#ifndef _SPRITE_H_
#define _SPRITE_H_

#include "Types.h"
#include "Animation.h"
#include "Vector2.h"
#include <map>

class Sprite
{
public:
    enum
    {
        AnimationDefault = 0
    };

    Sprite();
    Sprite( UInt32 width,
            UInt32 height );
    ~Sprite();

    void addAnimation(int id, const Animation& animation);

    void draw(UInt32 deltaMs);

    void startAnimation(int id);

    bool animationFinished() const;

    const Vector2& pos() const { return pos_; }
    void setPos(const Vector2& pos) { pos_ = pos; }

private:
    typedef std::map<int, Animation> AnimationMap;

    Vector2 pos_;
    UInt32 width_;
    UInt32 height_;
    AnimationMap animations_;
    int curAnimationId_;
    UInt32 curAnimationTimeMs_;
};

#endif

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
        AnimationNone    = -1,
        AnimationDefault = 0
    };

    Sprite();
    Sprite( UInt32 width,
            UInt32 height );
    ~Sprite();

    void addAnimation(int id, const Animation& animation);

    void render(UInt32 deltaMs, bool debug = false);

    void startAnimation(int id);

    inline int currentAnimationId() const { return curAnimationId_; }

    bool animationFinished() const;

    inline Vector2& pos() { return pos_; }

    inline const Vector2& pos() const { return pos_; }

    inline UInt32 width() const { return width_; }

    inline UInt32 height() const { return height_; }

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

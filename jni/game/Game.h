#ifndef _GAME_H_
#define _GAME_H_

#include "Types.h"
#include "TextureCollection.h"
#include "Sprite.h"
#include "Brick.h"

class Game
{
public:
    Game(const std::string& apkPath);
    ~Game();

    void init(UInt32 width, UInt32 height);

    void render();

private:
    static const UInt32 profileReportTimeoutMs_ = 3000;
    static const UInt32 maxFPS_ = 60;

    static UInt64 getTimeMs();

    Sprite createBackground(const Texture& texture);
    Brick createBrick(const Texture& texture);

    std::string apkPath_;

    TextureCollection textureCollection_;

    UInt32 gameWidth_;
    UInt32 gameHeight_;
    UInt32 viewWidth_;
    UInt32 viewHeight_;

    Sprite bg_;
    Brick brick_;

    UInt64 lastTimeMs_;
    UInt32 numFrames_;
    UInt32 accumRenderTimeMs_;
    UInt32 accumTimeMs_;
    UInt64 lastProfileReportTimeMs_;
};

#endif

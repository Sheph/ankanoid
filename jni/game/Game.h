#ifndef _GAME_H_
#define _GAME_H_

#include "Types.h"
#include "TextureCollection.h"
#include "Background.h"
#include "Brick.h"
#include "Paddle.h"
#include "Ball.h"

class Game
{
public:
    Game(const std::string& apkPath);
    ~Game();

    void init(UInt32 width, UInt32 height);

    void render();

private:
    static const UInt32 profileReportTimeoutMs_ = 3000;

    static UInt64 getTimeMs();

    Background createBackground(const Texture& texture);
    Brick createBrick(const Texture& texture);
    Paddle createPaddle(const Texture& texture);
    Ball createBall(const Texture& texture);

    std::string apkPath_;

    TextureCollection textureCollection_;

    UInt32 gameWidth_;
    UInt32 gameHeight_;
    UInt32 viewWidth_;
    UInt32 viewHeight_;

    Background bg_;
    Brick brick_;
    Paddle paddle_;
    Ball ball_;

    UInt64 lastTimeMs_;
    UInt32 numFrames_;
    UInt32 accumRenderTimeMs_;
    UInt32 accumTimeMs_;
    UInt64 lastProfileReportTimeMs_;
};

#endif

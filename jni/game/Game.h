#ifndef _GAME_H_
#define _GAME_H_

#include "Types.h"
#include "TextureCollection.h"
#include "Background.h"
#include "Brick.h"
#include "Paddle.h"
#include "Ball.h"
#include <vector>

class Game
{
public:
    Game(const std::string& apkPath);
    ~Game();

    void init(UInt32 width, UInt32 height);

    void input(UInt32 viewX, UInt32 viewY, bool up);

    void render();

    static const UInt32 profileReportTimeoutMs_ = 5000;
    static const float paddleSpeed_ = 400;
    static const float ballSpeed_ = 650;
    static const float ballReleaseAngleDeg_ = 15;
    static const float paddleMaxAngleDeg_ = 60;

private:
    static UInt64 getTimeMs();

    Background createBackground(const TexturePtr& texture);
    Brick createBrick(const TexturePtr& texture);
    Paddle createPaddle(const TexturePtr& texture);
    Ball createBall(const TexturePtr& texture);
    Sprite createWonBanner(const TexturePtr& texture);
    Sprite createLostBanner(const TexturePtr& texture);

    void resetLevel();

    void putBallOnPaddle();

    void viewXYToGameXY(UInt32& x, UInt32& y);

    void updatePaddle(UInt32 deltaMs);

    void updateBall(UInt32 deltaMs);

    void updateStatus(UInt32 deltaMs);

    bool initialized_;

    bool debug_;

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
    Sprite wonBanner_;
    Sprite lostBanner_;
    UInt32 lastXInput_;
    bool ballReleasePressed_;
    bool ballReleased_;

    UInt64 lastTimeMs_;
    UInt32 numFrames_;
    UInt32 accumRenderTimeMs_;
    UInt32 accumTimeMs_;
    UInt64 lastProfileReportTimeMs_;
};

#endif

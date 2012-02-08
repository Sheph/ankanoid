#include "Game.h"
#include "Logger.h"
#include "ZipWrapper.h"
#include <stdlib.h>
#include <assert.h>

Game::Game(const std::string& apkPath)
: debug_(false),
  apkPath_(apkPath),
  gameWidth_(480),
  gameHeight_(800),
  viewWidth_(gameWidth_),
  viewHeight_(gameHeight_),
  lastXInput_(0),
  ballReleasePressed_(false),
  ballReleased_(false),
  lastTimeMs_(0),
  numFrames_(0),
  accumRenderTimeMs_(0),
  accumTimeMs_(0),
  lastProfileReportTimeMs_(0)
{
    LOGI("Game::Game(%s)\n", apkPath_.c_str());
}

Game::~Game()
{
}

void Game::init(UInt32 width, UInt32 height)
{
    LOGI("Game::init(%d, %d)\n", width, height);

    viewWidth_ = width;
    viewHeight_ = height;

    glViewport(0, 0, viewWidth_, viewHeight_);
    glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrthox(0, (gameWidth_ - 1), 0, (gameHeight_ - 1), 0, 1);
    glMatrixMode(GL_MODELVIEW);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_TEXTURE_2D);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);

    ZipWrapper zip(apkPath_);

    if (!zip.archive())
    {
        LOGE("Cannot open zip file \"%s\"\n", apkPath_.c_str());
    }

    Texture bgTexture;
    Texture gameTexture;

    textureCollection_.addTexture(zip.archive(), "assets/sprites/background.png", bgTexture);
    textureCollection_.addTexture(zip.archive(), "assets/sprites/game.png", gameTexture);

    bg_ = createBackground(bgTexture);
    brick_ = createBrick(gameTexture);
    paddle_ = createPaddle(gameTexture);
    ball_ = createBall(gameTexture);

    resetLevel();
}

void Game::input(UInt32 viewX, UInt32 viewY, bool up)
{
    UInt32 x = viewX, y = viewY;

    viewXYToGameXY(x, y);

    lastXInput_ = x;

    if (up)
    {
        ballReleasePressed_ = true;
    }
}

void Game::render()
{
    UInt64 timeMs = getTimeMs();
    UInt32 deltaMs = 0;

    if (lastTimeMs_ == 0)
    {
        lastTimeMs_ = timeMs;
        lastProfileReportTimeMs_ = timeMs;
    }
    else
    {
        deltaMs = (timeMs - lastTimeMs_);
    }

    lastTimeMs_ = timeMs;

    /*
     * Update stuff
     */

    updatePaddle(deltaMs);

    updateBall(deltaMs);

    /*
     * Draw stuff
     */

    glClear(GL_COLOR_BUFFER_BIT);

    bg_.render(deltaMs, debug_);
    brick_.render(deltaMs, debug_);
    paddle_.render(deltaMs, debug_);
    ball_.render(deltaMs, debug_);

    UInt64 timeMs2 = getTimeMs();

    accumRenderTimeMs_ += (timeMs2 - timeMs);
    accumTimeMs_ += deltaMs;
    ++numFrames_;

    if ((timeMs2 - lastProfileReportTimeMs_) > profileReportTimeoutMs_)
    {
        lastProfileReportTimeMs_ = timeMs2;

        LOGI( "Render profile\nFPS: %d\nAverage render time: %d",
               (numFrames_ * 1000) / accumTimeMs_,
               accumRenderTimeMs_ / numFrames_ );

        accumRenderTimeMs_ = 0;
        accumTimeMs_ = 0;
        numFrames_ = 0;
    }
}

UInt64 Game::getTimeMs()
{
    /*
     * TODO: use monotonic clock
     */

    struct timeval tv;

    gettimeofday(&tv, NULL);

    return ((UInt64)tv.tv_sec * 1000U) + ((UInt64)tv.tv_usec / 1000U);
}

Background Game::createBackground(const Texture& texture)
{
    static const UInt32 bgTexWidth = 257;
    static const UInt32 bgTexHeight = 512;

    Sprite sprite(gameWidth_, gameHeight_);

    Animation defAnimation(texture, false);

    defAnimation.addFrame(AnimationFrame(0, 0, bgTexWidth, bgTexHeight, 0));

    sprite.addAnimation(Sprite::AnimationDefault, defAnimation);

    Background background(
        sprite,
        (26 * gameWidth_) / bgTexWidth,
        ((bgTexWidth - 26) * gameWidth_) / bgTexWidth );

    background.sprite().startAnimation(Sprite::AnimationDefault);

    return background;
}

Brick Game::createBrick(const Texture& texture)
{
    Sprite sprite(70, 38);

    Animation defAnimation(texture, true);

    defAnimation.addFrame(AnimationFrame(0,      0, 70, 38, 1000));
    defAnimation.addFrame(AnimationFrame(70,     0, 70, 38, 150));
    defAnimation.addFrame(AnimationFrame(70 * 2, 0, 70, 38, 150));
    defAnimation.addFrame(AnimationFrame(70 * 3, 0, 70, 38, 150));
    defAnimation.addFrame(AnimationFrame(70 * 2, 0, 70, 38, 150));
    defAnimation.addFrame(AnimationFrame(70,     0, 70, 38, 150));

    sprite.addAnimation(Sprite::AnimationDefault, defAnimation);

    Animation dieAnimation(texture, false);

    dieAnimation.addFrame(AnimationFrame(0,      38, 70, 38, 150));
    dieAnimation.addFrame(AnimationFrame(70,     38, 70, 38, 150));
    dieAnimation.addFrame(AnimationFrame(70 * 2, 38, 70, 38, 150));
    dieAnimation.addFrame(AnimationFrame(70 * 3, 38, 70, 38, 150));
    dieAnimation.addFrame(AnimationFrame(70 * 4, 38, 70, 38, 150));
    dieAnimation.addFrame(AnimationFrame(70 * 5, 38, 70, 38, 150));

    sprite.addAnimation(Brick::AnimationDie, dieAnimation);

    Brick brick(sprite, Vector2(0, 6), 64, 32);

    brick.sprite().startAnimation(Sprite::AnimationDefault);

    return brick;
}

Paddle Game::createPaddle(const Texture& texture)
{
    Sprite sprite(100, 30);

    Animation defAnimation(texture, false);

    defAnimation.addFrame(AnimationFrame(0, 76, 100, 30, 0));

    sprite.addAnimation(Sprite::AnimationDefault, defAnimation);

    Paddle paddle(sprite, Vector2(0, 6), 95, 24);

    paddle.sprite().startAnimation(Sprite::AnimationDefault);

    return paddle;
}

Ball Game::createBall(const Texture& texture)
{
    Sprite sprite(24, 24);

    Animation defAnimation(texture, false);

    defAnimation.addFrame(AnimationFrame(0, 106, 16, 16, 0));

    sprite.addAnimation(Sprite::AnimationDefault, defAnimation);

    Ball ball(sprite);

    ball.sprite().startAnimation(Sprite::AnimationDefault);

    return ball;
}

void Game::resetLevel()
{
    srand(time(NULL));

    UInt32 brickX =
        bg_.left() + (rand() % (bg_.right() - bg_.left() - brick_.sprite().width()));
    UInt32 brickY =
        300 + (rand() % (gameHeight_ - brick_.sprite().height() - 300));

    brick_.sprite().pos() = Vector2(brickX, brickY);

    UInt32 paddleX = (bg_.left() + bg_.right()) / 2 - (paddle_.sprite().width() / 2);
    UInt32 paddleY = 100;

    paddle_.sprite().pos() = Vector2(paddleX, paddleY);
    paddle_.speed() = Vector2(0, 0);

    lastXInput_ = paddle_.boundAbsCenter().x();

    putBallOnPaddle();

    ball_.speed() = Vector2(0, 0);

    ballReleasePressed_ = false;
    ballReleased_ = false;
}

void Game::putBallOnPaddle()
{
    Vector2 pos = paddle_.boundAbsPos();

    UInt32 ballX = pos.x() + paddle_.boundWidth() / 2 - ball_.sprite().width() / 2;
    UInt32 ballY = pos.y() + paddle_.boundHeight();

    ball_.sprite().pos() = Vector2(ballX, ballY);
}

void Game::viewXYToGameXY(UInt32& x, UInt32& y)
{
    x = (gameWidth_ * x) / viewWidth_;
    y = gameHeight_ - ((gameHeight_ * y) / viewHeight_);
}

void Game::updatePaddle(UInt32 deltaMs)
{
    float deltaS = ((float)deltaMs / 1000.0f);

    Vector2 boundCenter = paddle_.boundAbsCenter();

    /*
     * Make paddle "run to" last press position
     */

    if ((UInt32)boundCenter.x() == lastXInput_)
    {
        return;
    }
    else if ((UInt32)boundCenter.x() > lastXInput_)
    {
        paddle_.speed() = Vector2(-paddleSpeed_, 0);
    }
    else
    {
        paddle_.speed() = Vector2(paddleSpeed_, 0);
    }

    Vector2 newCenter = boundCenter + (paddle_.speed() * deltaS);

    if ( (newCenter.x() > lastXInput_) && (paddle_.speed().x() > 0) )
    {
        newCenter.setX(lastXInput_);
    }
    else if ( (newCenter.x() < lastXInput_) && (paddle_.speed().x() < 0) )
    {
        newCenter.setX(lastXInput_);
    }

    paddle_.sprite().pos() += (newCenter - boundCenter);

    /*
     * Constraint game area
     */

    if (paddle_.sprite().pos().x() < bg_.left())
    {
        paddle_.sprite().pos().setX(bg_.left());
    }

    if (paddle_.sprite().pos().x() + paddle_.sprite().width() > bg_.right())
    {
        paddle_.sprite().pos().setX(bg_.right() - paddle_.sprite().width());
    }
}

void Game::updateBall(UInt32 deltaMs)
{
    float deltaS = ((float)deltaMs / 1000.0f);

    if (!ballReleasePressed_)
    {
        putBallOnPaddle();

        return;
    }

    if (!ballReleased_)
    {
        ballReleased_ = true;

        Vector2 speed(0, ballSpeed_);

        speed.rotateClockwise(ballReleaseAngleDeg_);

        ball_.speed() = speed;
    }

    ball_.sprite().pos() += ball_.speed() * deltaS;
}

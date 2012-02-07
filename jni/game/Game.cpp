#include "Game.h"
#include "Logger.h"
#include <assert.h>

Game::Game()
: gameWidth_(320),
  gameHeight_(480),
  viewWidth_(gameWidth_),
  viewHeight_(gameHeight_),
  lastTimeMs_(0),
  numFrames_(0),
  accumRenderTimeMs_(0),
  accumTimeMs_(0),
  lastProfileReportTimeMs_(0)
{
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
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrthox(0, gameWidth_, 0, gameHeight_, 0, 1);
    glMatrixMode(GL_MODELVIEW);

    Sprite sprite(70, 38);

    Texture texture;

    bool res = textureCollection_.addTexture("assets/sprites/game.png", texture);
    assert(res);

    Animation defAnimation(texture, true);

    defAnimation.addFrame(AnimationFrame(0,      0, 70, 38, 1000));
    defAnimation.addFrame(AnimationFrame(70,     0, 70, 38, 250));
    defAnimation.addFrame(AnimationFrame(70 * 2, 0, 70, 38, 250));
    defAnimation.addFrame(AnimationFrame(70 * 3, 0, 70, 38, 250));
    defAnimation.addFrame(AnimationFrame(70 * 2, 0, 70, 38, 250));
    defAnimation.addFrame(AnimationFrame(70,     0, 70, 38, 250));

    sprite.addAnimation(Sprite::AnimationDefault, defAnimation);

    Animation dieAnimation(texture, true);

    dieAnimation.addFrame(AnimationFrame(0,      70, 70, 38, 250));
    dieAnimation.addFrame(AnimationFrame(70,     70, 70, 38, 250));
    dieAnimation.addFrame(AnimationFrame(70 * 2, 70, 70, 38, 250));
    dieAnimation.addFrame(AnimationFrame(70 * 3, 70, 70, 38, 250));
    dieAnimation.addFrame(AnimationFrame(70 * 4, 70, 70, 38, 250));
    dieAnimation.addFrame(AnimationFrame(70 * 5, 70, 70, 38, 250));

    sprite.addAnimation(Brick::AnimationDie, dieAnimation);

    brick_ = Brick(sprite, Vector2(0, 6), 64, 32);

    brick_.sprite().startAnimation(Sprite::AnimationDefault);
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

    glClear(GL_COLOR_BUFFER_BIT);

    brick_.sprite().render(deltaMs);

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

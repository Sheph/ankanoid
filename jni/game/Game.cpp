#include "Game.h"
#include "Logger.h"
#include "ZipWrapper.h"
#include <assert.h>

Game::Game(const std::string& apkPath)
: apkPath_(apkPath),
  gameWidth_(480),
  gameHeight_(800),
  viewWidth_(gameWidth_),
  viewHeight_(gameHeight_),
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

    brick_.sprite().setPos(Vector2(10, 10));

    bg_.render(deltaMs, true);
    brick_.render(deltaMs, true);

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

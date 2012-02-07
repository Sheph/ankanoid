#include "Game.h"
#include "Logger.h"
#include <assert.h>

Game::Game()
: gameWidth_(320),
  gameHeight_(480),
  viewWidth_(gameWidth_),
  viewHeight_(gameHeight_)
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

    Sprite sprite(32, 32);

    Texture texture;

    bool res = textureCollection_.addTexture("res/drawable/brick.png", texture);
    assert(res);

    Animation defAnimation(texture, true);

    for (UInt32 i = 0; i < 5; ++i)
    {
        defAnimation.addFrame(AnimationFrame(32 * i, 0, 32, 32, 1000));
    }

    sprite.addAnimation(Sprite::AnimationDefault, defAnimation);

    Animation dieAnimation(texture, true);

    for (UInt32 i = 0; i < 5; ++i)
    {
        dieAnimation.addFrame(AnimationFrame(32 * i, 32, 32, 32, 1000));
    }

    sprite.addAnimation(Brick::AnimationDie, dieAnimation);

    brick_ = Brick(sprite, Vector2(2, 2), 28, 28);
}

void Game::render()
{

}

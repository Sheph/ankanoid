#ifndef _GAME_H_
#define _GAME_H_

#include "Types.h"
#include "TextureCollection.h"
#include "Brick.h"

class Game
{
public:
    Game();
    ~Game();

    void init(UInt32 width, UInt32 height);

    void render();

private:
    TextureCollection textureCollection_;

    UInt32 gameWidth_;
    UInt32 gameHeight_;
    UInt32 viewWidth_;
    UInt32 viewHeight_;

    Brick brick_;
};

#endif

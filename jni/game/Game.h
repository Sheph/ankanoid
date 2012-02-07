#ifndef _GAME_H_
#define _GAME_H_

#include <GLES/gl.h>
#include <math.h>

class Game
{
public:
    Game();
    ~Game();

    void resize(GLsizei width, GLsizei height);

    void render();

private:
    GLsizei width_;
    GLsizei height_;

};

#endif

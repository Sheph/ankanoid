#include "Game.h"
#include <android/log.h>

#define LOG_TAG "ankanoid"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG,__VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG,__VA_ARGS__)

Game::Game()
{
}

Game::~Game()
{
}

void Game::resize(GLsizei width, GLsizei height)
{
    LOGI("Game::resize(%d, %d)\n", width, height);

    glViewport(0, 0, width, height);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrthox(0, width, 0, height, 0, 1);
    glMatrixMode(GL_MODELVIEW);
}

void Game::render()
{
    GLfixed vertices[] =
    {
        5, 5,
        5, 10,
        10, 5,
        10, 10
   };

   glEnableClientState(GL_VERTEX_ARRAY);

   glColor4f(0.0f, 1.0f, 0.0f, 1.0f);

   glVertexPointer(2, GL_FIXED, 0, &vertices[0]);

   glDrawArrays(GL_TRIANGLE_STRIP, 0, sizeof(vertices) / (2 * sizeof(GLfixed)));

   glDisableClientState(GL_VERTEX_ARRAY);
}

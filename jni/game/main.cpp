#include <jni.h>
#include <android/log.h>
#include "Game.h"

static Game* gGame = NULL;

extern "C"
{
    JNIEXPORT void JNICALL Java_com_ankanoid_AnkanoidJNILib_init(JNIEnv* env, jobject obj)
    {
        if (!gGame)
        {
            gGame = new Game();
        }
    }

    JNIEXPORT void JNICALL Java_com_ankanoid_AnkanoidJNILib_resize(JNIEnv* env, jobject obj, jint width, jint height)
    {
        if (gGame)
        {
            gGame->init(width, height);
        }
    }

    JNIEXPORT void JNICALL Java_com_ankanoid_AnkanoidJNILib_render(JNIEnv* env, jobject obj)
    {
        if (gGame)
        {
            gGame->render();
        }
    }
};

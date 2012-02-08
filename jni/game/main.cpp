#include <jni.h>
#include <android/log.h>
#include "Game.h"

static Game* gGame = NULL;

extern "C"
{
    JNIEXPORT void JNICALL Java_com_ankanoid_AnkanoidJNILib_init(JNIEnv* env, jobject obj, jstring apkPath)
    {
        if (!gGame)
        {
            jboolean isCopy;

            const char* str = env->GetStringUTFChars(apkPath, &isCopy);

            gGame = new Game(str);

            env->ReleaseStringUTFChars(apkPath, str);
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

    JNIEXPORT void JNICALL Java_com_ankanoid_AnkanoidJNILib_input(JNIEnv* env, jobject obj, jint x, jint y, jboolean up)
    {
        if (gGame)
        {
            gGame->input(x, y, up);
        }
    }
};

LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := libankanoidjni
LOCAL_C_INCLUDES := $(LOCAL_PATH)/../libz/ $(LOCAL_PATH)/../libpng/ $(LOCAL_PATH)/../libzip/
LOCAL_STATIC_LIBRARIES := libpng libzip libz
LOCAL_CFLAGS := -Wall
LOCAL_SRC_FILES := main.cpp Game.cpp PNGSource.cpp PNGUtils.cpp PNGDecoder.cpp TextureCollection.cpp Animation.cpp Sprite.cpp
LOCAL_LDLIBS := -llog -lGLESv1_CM

include $(BUILD_SHARED_LIBRARY)

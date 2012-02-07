LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := libankanoidjni
LOCAL_CFLAGS    := -Wall
LOCAL_SRC_FILES := main.cpp Game.cpp
LOCAL_LDLIBS    := -llog -lGLESv1_CM

include $(BUILD_SHARED_LIBRARY)

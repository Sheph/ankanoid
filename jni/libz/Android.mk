LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := libz
LOCAL_SRC_FILES := \
    adler32.c \
    compress.c \
    crc32.c \
    deflate.c \
    gzclose.c \
    gzlib.c \
    gzread.c \
    gzwrite.c \
    inflate.c \
    infback.c \
    inftrees.c \
    inffast.c \
    trees.c \
    uncompr.c \
    zutil.c

include $(BUILD_STATIC_LIBRARY)

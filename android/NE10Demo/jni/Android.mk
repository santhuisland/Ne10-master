LOCAL_PATH := $(call my-dir)
ROOT_PATH := $(call my-dir)/../
$(info $(ROOT_PATH))
include $(CLEAR_VARS)

include $(CLEAR_VARS)
LOCAL_MODULE := NE10
LOCAL_EXPORT_C_INCLUDES := ../../../inc
LOCAL_SRC_FILES := ../Supportedfiles/libs/libNE10.so
include $(PREBUILT_SHARED_LIBRARY)


include $(CLEAR_VARS)

LOCAL_CPPFLAGS += -fexceptions

LOCAL_SHARED_LIBRARIES := NE10

#LOCAL_ARM_MODE := arm

TARGET_PIE := false
NDK_APP_PIE := false

LOCAL_LDLIBS := -L$(SYSROOT)/usr/lib -llog

LOCAL_MODULE    := NE10_test_demo
LOCAL_SRC_FILES := NE10_test_demo.cpp

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../../inc
LOCAL_CFLAGS := -L
LOCAL_CPPFLAGS := -fPIE
LOCAL_CFLAGS += -fPIE -pie
LOCAL_LDFLAGS := -fPIE
LOCAL_LDFLAGS +:= -pie
#LOCAL_LDLIBS := -lNE10_test

include $(BUILD_SHARED_LIBRARY)

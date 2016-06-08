LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

$(call import-add-path,$(LOCAL_PATH)/../../../cocos2d)
$(call import-add-path,$(LOCAL_PATH)/../../../cocos2d/external)
$(call import-add-path,$(LOCAL_PATH)/../../../cocos2d/cocos)
$(call import-add-path,$(LOCAL_PATH)/../../../cocos2d/cocos/audio/include)

LOCAL_MODULE := MyGame_shared

LOCAL_MODULE_FILENAME := libMyGame

LOCAL_SRC_FILES := hellocpp/main.cpp \
                   ../../../Classes/AppDelegate.cpp \
                   ../../../Classes/HelloWorldScene.cpp \
                   ../../../Classes/BannerMenuScene.cpp \
                   ../../../Classes/BannerViewScene.cpp \
                   ../../../Classes/BannerViewWithSpotIDScene.cpp \
                   ../../../Classes/IconMenuScene.cpp \
                   ../../../Classes/IconMenuWithSpotIDScene.cpp \
                   ../../../Classes/InterstitialMenuScene.cpp \
                   ../../../Classes/NativeMenuScene.cpp \
                   ../../../Classes/NativeViewScene.cpp \
                   ../../../Classes/NativeInfeedViewScene.cpp \
                   ../../../Classes/NativeTelopViewScene.cpp \
                   ../../../Classes/Common/NendHttpHelper.cpp \
                   ../../../Classes/Common/NendNativeAdClient.cpp \
                   ../../../Classes/Common/NendNativeAdLog.cpp \
                   ../../../Classes/Common/NendNativeAdRender.cpp \
                   ../../../Classes/Common/NendNativeAdValidate.cpp \
                   ../../../Classes/Common/NendNativeAdViewHolder.cpp \
                   ../../../Classes/Common/NendNativeClipNodeConstraint.cpp \
                   ../../../Classes/Common/NendNativeClippingNode.cpp \
                   ../../../Classes/Common/NendNativeLabel.cpp \
                   ../../../Classes/Common/NendNativeLabelConstraint.cpp \
                   ../../../Classes/Common/NendNativeSprite.cpp \
                   ../../../Classes/Common/NendNativeSpriteConstraint.cpp \
                   ../../../Classes/Android/AndroidNativeAd.cpp \
                   ../../../Classes/Android/AndroidNativeAdClient.cpp \
                   ../../../Classes/Android/AndroidNativeJNI.cpp \
                   ../../../Classes/Android/NendIconModule.cpp \
                   ../../../Classes/Android/NendInterstitialModule.cpp \
                   ../../../Classes/Android/NendModule.cpp

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../../Classes
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../../Classes/Common
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../../Classes/Android

# _COCOS_HEADER_ANDROID_BEGIN
# _COCOS_HEADER_ANDROID_END


LOCAL_STATIC_LIBRARIES := cocos2dx_static

# _COCOS_LIB_ANDROID_BEGIN
# _COCOS_LIB_ANDROID_END

include $(BUILD_SHARED_LIBRARY)

$(call import-module,.)

# _COCOS_LIB_IMPORT_ANDROID_BEGIN
# _COCOS_LIB_IMPORT_ANDROID_END

LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

$(call import-add-path,$(LOCAL_PATH)/../../../cocos2d)
$(call import-add-path,$(LOCAL_PATH)/../../../cocos2d/external)
$(call import-add-path,$(LOCAL_PATH)/../../../cocos2d/cocos)
$(call import-add-path,$(LOCAL_PATH)/../../../cocos2d/cocos/audio/include)

LOCAL_MODULE := MyGame_shared

LOCAL_MODULE_FILENAME := libMyGame

LOCAL_SRC_FILES := $(LOCAL_PATH)/hellocpp/main.cpp \
                   $(LOCAL_PATH)/../../../Classes/AppDelegate.cpp \
                   $(LOCAL_PATH)/../../../Classes/HelloWorldScene.cpp \
                   $(LOCAL_PATH)/../../../Classes/BannerMenuScene.cpp \
                   $(LOCAL_PATH)/../../../Classes/BannerViewScene.cpp \
                   $(LOCAL_PATH)/../../../Classes/BannerViewWithSpotIDScene.cpp \
                   $(LOCAL_PATH)/../../../Classes/IconMenuScene.cpp \
                   $(LOCAL_PATH)/../../../Classes/IconMenuWithSpotIDScene.cpp \
                   $(LOCAL_PATH)/../../../Classes/InterstitialMenuScene.cpp \
                   $(LOCAL_PATH)/../../../Classes/NativeMenuScene.cpp \
                   $(LOCAL_PATH)/../../../Classes/NativeCustomViewScene.cpp \
                   $(LOCAL_PATH)/../../../Classes/NativeViewScene.cpp \
                   $(LOCAL_PATH)/../../../Classes/NativeInfeedViewScene.cpp \
                   $(LOCAL_PATH)/../../../Classes/NativeTelopViewScene.cpp \
                   $(LOCAL_PATH)/../../../Classes/FullBoardAdScene.cpp \
                   $(LOCAL_PATH)/../../../Classes/VideoAdScene.cpp \
                   $(LOCAL_PATH)/../../../Classes/Common/NendNativeLabel.cpp \
                   $(LOCAL_PATH)/../../../Classes/Common/NendNativeSprite.cpp \
                   $(LOCAL_PATH)/../../../Classes/Common/NendNativeClippingNode.cpp \
                   $(LOCAL_PATH)/../../../Classes/Common/NendNativeAdClient.cpp \
                   $(LOCAL_PATH)/../../../Classes/Common/NendHttpHelper.cpp \
                   $(LOCAL_PATH)/../../../Classes/Common/NendNativeAdLog.cpp \
                   $(LOCAL_PATH)/../../../Classes/Common/NendNativeAdRender.cpp \
                   $(LOCAL_PATH)/../../../Classes/Common/NendNativeAdBinder.cpp \
                   $(LOCAL_PATH)/../../../Classes/Common/NendNativeAd.cpp \
                   $(LOCAL_PATH)/../../../Classes/Common/NendNativeImpressionTracker.cpp \
                   $(LOCAL_PATH)/../../../Classes/Common/NendVideoAd.cpp \
                   $(LOCAL_PATH)/../../../Classes/Android/NendModule.cpp \
                   $(LOCAL_PATH)/../../../Classes/Android/NendIconModule.cpp \
                   $(LOCAL_PATH)/../../../Classes/Android/NendInterstitialModule.cpp \
                   $(LOCAL_PATH)/../../../Classes/Android/AndroidNativeAd.cpp \
                   $(LOCAL_PATH)/../../../Classes/Android/AndroidNativeJNI.cpp \
                   $(LOCAL_PATH)/../../../Classes/Android/AndroidNativeAdClient.cpp \
                   $(LOCAL_PATH)/../../../Classes/Android/NendFullBoardAd.cpp \
                   $(LOCAL_PATH)/../../../Classes/Android/NendAdJniUtils.cpp \
                   $(LOCAL_PATH)/../../../Classes/Android/NendInterstitialVideoAd.cpp \
                   $(LOCAL_PATH)/../../../Classes/Android/NendRewardedVideoAd.cpp \
                   $(LOCAL_PATH)/../../../Classes/Android/NendUserFeature.cpp \
                   $(LOCAL_PATH)/../../../Classes/Common/NendLogger.cpp \
                   $(LOCAL_PATH)/../../../Classes/Android/AndroidNendLogger.cpp

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

//
//  NendInterstitialModule.h
//
//  Created by F@N Communications, Inc.
//
//

#ifndef cocos2dxv32test2_NendInterstitialModule_h
#define cocos2dxv32test2_NendInterstitialModule_h

#include "cocos2d.h"
#include <stdarg.h>

#define NADInterstitialDelegateLoadResultNotification               "NEND_INTERSTITIAL_DELEGATE_LOAD_RESULT_NOTIFICATION"
#define NADInterstitialDelegateLoadResultWithSpotIdNotification     "NEND_INTERSTITIAL_DELEGATE_LOAD_RESULT_WITH_SPOTID_NOTIFICATION"
#define NADInterstitialDelegateShowResultNotification               "NEND_INTERSTITIAL_DELEGATE_SHOW_RESULT_NOTIFICATION"
#define NADInterstitialDelegateShowResultWithSpotIdNotification     "NEND_INTERSTITIAL_DELEGATE_SHOW_RESULT_WITH_SPOTID_NOTIFICATION"
#define NADInterstitialDelegateClickResultNotification              "NEND_INTERSTITIAL_DELEGATE_CLICK_RESULT_NOTIFICATION"
#define NADInterstitialDelegateClickResultWithSpotIdNotification    "NEND_INTERSTITIAL_DELEGATE_CLICK_RESULT_WITH_SPOTID_NOTIFICATION"

typedef enum {
    FINISH_LOAD_AD_INTERSTITIAL,
    FAIL_AD_DOWNLOAD_INTERSTITIAL,
    INVALID_RESPONSE_TYPE_INTERSTITIAL,
    FAIL_AD_REQUEST_INTERSTITIAL,
    FAIL_AD_INCOMPLETE_INTERSTITIAL
} NADInterstitialDelegateLoadResultStatusCode;

typedef enum {
    SHOW_SUCCESS,
    SHOW_ALREADY,
    SHOW_FREQUENCY_NOT_REACHABLE,
    REQUEST_INCOMPLETE,
    LOAD_INCOMPLETE,
    DOWNLOAD_INCOMPLETE
} NADInterstitialDelegateShowResultStatusCode;

typedef enum {
    CLICK_DOWNLOAD,
    CLICK_CLOSE,
    CLICK_EXIT
} NADInterstitialDelegateClickResultStatusCode;

typedef enum {
    NAD_INTERSTITIAL_SUPPORTED_ORIENTATION_PORTRAIT = 1,
    NAD_INTERSTITIAL_SUPPORTED_ORIENTATION_PORTRAIT_UPSIDE_DOWN,
    NAD_INTERSTITIAL_SUPPORTED_ORIENTATION_LANDSCAPE_LEFT,
    NAD_INTERSTITIAL_SUPPORTED_ORIENTATION_LANDSCAPE_RIGHT
} NADInterstitialSupportedOrientation;


using namespace cocos2d;

class NendInterstitialModule
{
private:
    NendInterstitialModule();
    // シングルトン用クラス保持
    static NendInterstitialModule* m_mySingleton;
    
public:
    //クラス取得
    static NendInterstitialModule* sharedNendInterstitialModule();
    // NADInterstitial生成、API Key, NendIDを設定
    static void createNADInterstitial(char* apiKey, char* spotID);
    // NADInterstitial表示
    static void showNADInterstitialView();
    static void showNADInterstitialView(char* spotID);
    // NADInterstitial非表示
    static void dismissNADInterstitialView();
    // NADInterstitial表示向きを指定（※iOS用）
    static void setSupportedOrientations(int* orientations);
    // NADInterstitial終了時広告（※Android用）
    static void showFinishNADInterstitialView();
    static void showFinishNADInterstitialView(char* spotID);
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    // EventDispatcherでデリゲート結果を通知する
    static void sendEventDispatcherLoadResult(int resultCode, char* spotID);
    static void sendEventDispatcherShowResult(int resultCode, char* spotID);
    static void sendEventDispatcherClickResult(int resultCode, char* spotID);
#endif

};

#endif

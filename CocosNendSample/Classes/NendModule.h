//
//  NendModule.h
//
//  Created by F@N Communications, Inc.
//
//

#ifndef __NendModule__
#define __NendModule__

#include "cocos2d.h"

#define NADViewDelegateNotification     "NENDVIEW_DELEGATE_NOTIFICATION"

typedef enum {
    FINISH_LOAD_AD,
    RECEIVE_AD,
    FAIL_TO_RECEIVE_AD,
    CLICK_AD,
    DISMISS_SCREEN
} NADViewDelegateStatusCode;

typedef enum {
    TOP,
    BOTTOM,
    USER
} NADViewLayoutType;

using namespace cocos2d;

class NendModule
{
private:
    NendModule();
    //シングルトン用クラス保持
    static NendModule* m_mySingleton;
    //NADView生成、API Key、NendID、バナーサイズ自動調整を設定
    static void createNADView(char* apiKey, char* spotID, bool isAdjust);
    //内部動作用　広告のload
    static void load();
public:
    //クラス取得
    static NendModule* sharedNendModule();

    //NADView生成、API Key、NendID、位置を設定
    static void createNADView(char* apiKey, char* spotID, cocos2d::Point pos);
    //NADView生成、API Key、NendID、位置、バナーサイズ自動調整を設定
    static void createNADView(char* apiKey, char* spotID, cocos2d::Point pos, bool isAdjust);

    //NADView生成、画面上部、API Key、NendIDを設定
    static void createNADViewTop(char* apiKey, char* spotID);
    //NADView生成、画面上部、API Key、NendID、バナーサイズ自動調整を設定
    static void createNADViewTop(char* apiKey, char* spotID, bool isAdjust);

    //NADView生成、画面下部、API Key、NendIDを設定
    static void createNADViewBottom(char* apiKey, char* spotID);
    //NADView生成、画面下部、API Key、NendID、バナーサイズ自動調整を設定
    static void createNADViewBottom(char* apiKey, char* spotID, bool isAdjust);

    //NADView非表示
    static void hideNADView();
    //NADView表示
    static void showNADView();
    //広告のload一時停止
    static void pause();
    //広告のload再開
    static void resume();
    //解放
    static void release();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    // EventDispatcherでデリゲート結果を通知する
    static void sendEventDispatcher(int resultCode);
    // NADViewの表示位置を調整する
    static void layoutNADView();
#endif

};

#endif

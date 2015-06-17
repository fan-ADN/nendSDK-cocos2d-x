//
//  NendIconModule.h
//
//  Created by F@N Communications, Inc.
//
//

#ifndef __NendIconModule__
#define __NendIconModule__

#include "cocos2d.h"

#define NADIconLoaderDelegateNotification     "NEND_ICON_DELEGATE_NOTIFICATION"

typedef enum {
    FINISH_LOAD_AD_ICON,
    RECEIVE_AD_ICON,
    FAIL_TO_RECEIVE_AD_ICON,
    CLICK_AD_ICON
} NADIconLoaderDelegateStatusCode;

using namespace cocos2d;

class NendIconModule
{
private:
    NendIconModule();
    //シングルトン用クラス保持
    static NendIconModule* m_mySingleton;
public:
    //クラス取得
    static NendIconModule* sharedNendIconModule();
    //NADIconLoader生成
    static void createNADIconLoader(char* apiKey, char* spotID);
    //NADIconView生成、位置指定
    static void createNADIconView(cocos2d::Point pos);
    //NADIconView生成、画面下部
    static void createNADIconViewBottom();
    static void createNADIconViewBottom(int iconCount);
    //NADIconView生成、画面上部
    static void createNADIconViewTop();
    static void createNADIconViewTop(int iconCount);
    //NADIconView非表示
    static void hideNADIconView();
    //NADIconView表示
    static void showNADIconView();
    //広告のload
    static void load();
    //広告のload一時停止
    static void pause();
    //広告のload再開
    static void resume();
    //解放
    static void release();

};

#endif

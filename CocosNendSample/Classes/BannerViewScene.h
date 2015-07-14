//
//  BannerViewScene.h
//  HelloCpp
//
//  Created by F@N Communications, Inc.
//
//

#ifndef __HelloCpp__BannerViewScene__
#define __HelloCpp__BannerViewScene__

#include <stdio.h>
#include "cocos2d.h"

typedef enum {
    BANNER_320_50,
    BANNER_320_100,
    BANNER_300_100,
    BANNER_300_250,
    BANNER_728_90
} BannerSize;

class BannerViewScene : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene(BannerSize bannerSize);
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(BannerViewScene);
    
    virtual void onEnter();
    virtual void onExit();
    virtual void onExitTransitionDidStart();
    
    // メニューボタンのコールバック
    void createBannerTopCallback(cocos2d::Ref* pSender);
    void createBannerBottomCallback(cocos2d::Ref* pSender);
    void createBannerUserCallback(cocos2d::Ref* pSender);
    void showBannerCallback(cocos2d::Ref* pSender);
    void hideBannerCallback(cocos2d::Ref* pSender);
    void pauseBannerCallback(cocos2d::Ref* pSender);
    void resumeBannerCallback(cocos2d::Ref* pSender);
    void releaseBannerCallback(cocos2d::Ref* pSender);
    void showPreviousSceneButtonCallback(cocos2d::Ref* pSender);
    void isAdjustOnCallback(cocos2d::Ref* pSender);
    void isAdjustOffCallback(cocos2d::Ref* pSender);

    // EventDispatcher登録&削除
    void addEventDispatcher();
    void removeEventDispatcher();
};

#endif /* defined(__HelloCpp__BannerViewScene__) */

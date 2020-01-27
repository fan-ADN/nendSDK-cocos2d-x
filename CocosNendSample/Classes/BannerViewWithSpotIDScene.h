//
//  BannerViewWithSpotIDScene.h
//  CocosNendSample
//
//  Created by FAN Communications, Inc.
//
//

#ifndef __CocosNendSample__BannerViewWithSpotIDScene__
#define __CocosNendSample__BannerViewWithSpotIDScene__

#include <stdio.h>
#include "cocos2d.h"

class BannerViewWithSpotIDScene : public cocos2d::Scene
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(BannerViewWithSpotIDScene);
    
    virtual void onEnter();
    virtual void onExit();
    virtual void onExitTransitionDidStart();
    
    // メニューボタンのコールバック
    void createBannerTopCallback(cocos2d::Ref* pSender);
    void createBannerBottomCallback(cocos2d::Ref* pSender);
    void createBannerUserCallback(cocos2d::Ref* pSender);
    void showBannerCallback(cocos2d::Ref* pSender);
    void showBannerWithSpotIDCallback(cocos2d::Ref* pSender);
    void hideBannerCallback(cocos2d::Ref* pSender);
    void hideBannerWithSpotIDCallback(cocos2d::Ref* pSender);
    void pauseBannerCallback(cocos2d::Ref* pSender);
    void pauseBannerWithSpotIDCallback(cocos2d::Ref* pSender);
    void resumeBannerCallback(cocos2d::Ref* pSender);
    void resumeBannerWithSpotIDCallback(cocos2d::Ref* pSender);
    void releaseBannerCallback(cocos2d::Ref* pSender);
    void releaseBannerWithSpotIDCallback(cocos2d::Ref* pSender);
    void showPreviousSceneButtonCallback(cocos2d::Ref* pSender);
    void isAdjustOnCallback(cocos2d::Ref* pSender);
    void isAdjustOffCallback(cocos2d::Ref* pSender);
    
    // EventDispatcher登録&削除
    void addEventDispatcher();
    void removeEventDispatcher();
};

#endif /* defined(__CocosNendSample__BannerViewWithSpotIDScene__) */

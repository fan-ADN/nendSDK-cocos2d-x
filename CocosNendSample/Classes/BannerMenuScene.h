//
//  BannerMenuScene.h
//  HelloCpp
//
//  Created by F@N Communications, Inc.
//
//

#ifndef HelloCpp_BannerMenuScene_h
#define HelloCpp_BannerMenuScene_h

#include <stdio.h>
#include "cocos2d.h"

class BannerMenuScene : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(BannerMenuScene);
    
    // メニューボタンのコールバック
    void showBanner320_50ViewSceneButtonCallback(cocos2d::Ref* pSender);
    void showBanner320_100ViewSceneButtonCallback(cocos2d::Ref* pSender);
    void showBanner300_100ViewSceneButtonCallback(cocos2d::Ref* pSender);
    void showBanner300_250ViewSceneButtonCallback(cocos2d::Ref* pSender);
    void showBanner728_90ViewSceneButtonCallback(cocos2d::Ref* pSender);
    void showPreviousSceneButtonCallback(cocos2d::Ref* pSender);
};

#endif

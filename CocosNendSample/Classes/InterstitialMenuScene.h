//
//  InterstitialMenuScene.h
//  CocosNendSample
//
//  Created by FAN Communications, Inc.
//
//

#ifndef __HelloCpp__InterstitialMenuScene__
#define __HelloCpp__InterstitialMenuScene__

#include <stdio.h>
#include "cocos2d.h"

class InterstitialMenuScene : public cocos2d::Scene
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(InterstitialMenuScene);
    
    virtual void onEnter();
    virtual void onExit();
    
    // メニューボタンのコールバック
    void showInterstitialButtonCallback(cocos2d::Ref* pSender);
    void showInterstitialWithSpotIdButtonCallback(cocos2d::Ref* pSender);
    void hideInterstitialWithSpotIdButtonCallback(cocos2d::Ref* pSender);
    void showPreviousSceneButtonCallback(cocos2d::Ref* pSender);
    
    // EventDispatcher登録&削除
    void addEventDispatcher();
    void removeEventDispatcher();

    void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
};

#endif /* defined(__HelloCpp__InterstitialMenuScene__) */

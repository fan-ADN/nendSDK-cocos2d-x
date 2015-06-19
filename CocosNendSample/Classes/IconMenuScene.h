//
//  IconMenuScene.h
//  HelloCpp
//
//  Created by F@N Communications, Inc.
//
//

#ifndef __HelloCpp__IconMenuScene__
#define __HelloCpp__IconMenuScene__

#include <stdio.h>
#include "cocos2d.h"

class IconMenuScene : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(IconMenuScene);
    
    virtual void onEnter();
    virtual void onExit();
    
    // メニューボタンのコールバック
    void createIconTopCallback(cocos2d::Ref* pSender);
    void createIconBottomCallback(cocos2d::Ref* pSender);
    void createIconUserCallback(cocos2d::Ref* pSender);
    void createIconWithNumberTopCallback(cocos2d::Ref* pSender);
    void createIconWithNumberBottomCallback(cocos2d::Ref* pSender);
    void showIconCallback(cocos2d::Ref* pSender);
    void hideIconCallback(cocos2d::Ref* pSender);
    void pauseIconCallback(cocos2d::Ref* pSender);
    void resumeIconCallback(cocos2d::Ref* pSender);
    void releaseIconCallback(cocos2d::Ref* pSender);
    void showPreviousSceneButtonCallback(cocos2d::Ref* pSender);
    
    // EventDispatcher登録&削除
    void addEventDispatcher();
    void removeEventDispatcher();
};

#endif /* defined(__HelloCpp__IconMenuScene__) */

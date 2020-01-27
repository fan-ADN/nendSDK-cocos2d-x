//
//  IconMenuWithSpotIDScene.h
//  CocosNendSample
//
//  Created by FAN Communications, Inc.
//
//

#ifndef __HelloCpp__IconMenuWithSpotIDScene__
#define __HelloCpp__IconMenuWithSpotIDScene__

#include <stdio.h>
#include "cocos2d.h"

class IconMenuWithSpotIDScene : public cocos2d::LayerColor
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);

    // implement the "static create()" method manually
    CREATE_FUNC(IconMenuWithSpotIDScene);

    virtual void onEnter();
    virtual void onExit();
    virtual void onExitTransitionDidStart();

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
    void spaceAndTitleDisableCallback(cocos2d::Ref* pSender);
    void spaceDisableCallback(cocos2d::Ref* pSender);
    void titleDsableCallback(cocos2d::Ref* pSender);
    void showPreviousSceneButtonCallback(cocos2d::Ref* pSender);

    // EventDispatcher登録&削除
    void addEventDispatcher();
    void removeEventDispatcher();
};

#endif /* defined(__HelloCpp__IconMenuWithSpotIDScene__) */

//
//  NativeMenuScene.h
//  CocosNendSample
//
//  Created by FAN Communications, Inc.
//
//

#ifndef NativeMenuScene_h
#define NativeMenuScene_h

#include "cocos2d.h"
#include "NativeViewScene.h"

class NativeMenuScene : public cocos2d::Scene
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(NativeMenuScene);

    // メニューボタンのコールバック
    void showNativeCustomViewSceneButtonCallback(cocos2d::Ref* pSender);
    void showNativeViewSceneButtonCallback(cocos2d::Ref* pSender, NativeType type);
    void showNativeInfeedViewSceneButtonCallback(cocos2d::Ref* pSender);
    void showNativeTelopViewSceneButtonCallback(cocos2d::Ref* pSender);
    void showPreviousSceneButtonCallback(cocos2d::Ref* pSender);

};

#endif /* NativeMenuScene_h */

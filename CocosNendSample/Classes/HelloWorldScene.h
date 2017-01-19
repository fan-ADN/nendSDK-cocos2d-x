#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class HelloWorld : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
    
    // メニューボタンのコールバック
    void showBannerSceneButtonCallback(cocos2d::Ref* pSender);
    void showBannerWithSpotIDSceneButtonCallback(cocos2d::Ref* pSender);
    void showInterstitialSceneButtonCallback(cocos2d::Ref* pSender);
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    void showIconSceneButtonCallback(cocos2d::Ref* pSender);
#endif
    void showNativeAdSceneButtonCallback(cocos2d::Ref* pSender);
    void showFullBoardAdSceneButtonCallback(cocos2d::Ref* pSender);

private:
    cocos2d::MenuItem *createMenuItem(const std::string& title, const cocos2d::ccMenuCallback& callback);
};

#endif // __HELLOWORLD_SCENE_H__

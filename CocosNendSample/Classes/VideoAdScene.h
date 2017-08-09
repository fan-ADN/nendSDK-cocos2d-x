//
//  VideoAdScene.h
//  CocosNendSample
//

#ifndef VideoAdScene_h
#define VideoAdScene_h

#include "cocos2d.h"
#include "NendVideoAds.h"

class VideoAdScene : public cocos2d::Scene
{
public:
    ~VideoAdScene();
    
    static cocos2d::Scene* createScene();
    
    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(VideoAdScene);
    
private:

    std::unique_ptr<nend_module::video::VideoAds::InterstitialVideoAd> _interstitialVideoAd;
    std::unique_ptr<nend_module::video::VideoAds::RewardedVideoAd> _rewardedVideoAd;

    cocos2d::MenuItemLabel* _rewardStatus;
    cocos2d::MenuItemLabel* _interstitialStatus;

    // メニューボタンのコールバック
    void menuLoadRewardAdCallback(cocos2d::Ref* pSender);
    void menuShowRewardAdCallback(cocos2d::Ref* pSender);

    void menuLoadInterstitialAdCallback(cocos2d::Ref* pSender);
    void menuShowInterstitialAdCallback(cocos2d::Ref* pSender);

    
    void showPreviousSceneButtonCallback(cocos2d::Ref* pSender);
};

#endif /* VideoAdScene_h */

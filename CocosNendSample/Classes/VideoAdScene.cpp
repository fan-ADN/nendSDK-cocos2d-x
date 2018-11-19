//
//  VideoAdScene.cpp
//  CocosNendSample
//

#include "VideoAdScene.h"
#include "HelloWorldScene.h"

USING_NS_CC;
using namespace nend_module::video;

VideoAdScene::~VideoAdScene()
{
    _rewardedVideoAd->destroy();
    _interstitialVideoAd->destroy();
}

Scene* VideoAdScene::createScene()
{
    return VideoAdScene::create();
}

bool VideoAdScene::init()
{
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto label = Label::createWithTTF("VideoAd", "fonts/Marker Felt.ttf", 24);
    label->setPosition(Point(origin.x + visibleSize.width/2,
                             origin.y + visibleSize.height - label->getContentSize().height));
    this->addChild(label, 1);
    
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(VideoAdScene::showPreviousSceneButtonCallback, this));
    closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    const std::string font = StringUtils::format("fonts/arial.ttf");
    const float fontSize = 15.0f;

    
    Vector<MenuItem *> rewardMenuItems;
    rewardMenuItems.pushBack(MenuItemLabel::create(Label::createWithSystemFont("Reward Video", font, fontSize)));
    rewardMenuItems.pushBack(MenuItemLabel::create(Label::createWithSystemFont("LoadAd", font, fontSize), CC_CALLBACK_1(VideoAdScene::menuLoadRewardAdCallback, this)));
    rewardMenuItems.pushBack(MenuItemLabel::create(Label::createWithSystemFont("ShowAd", font, fontSize), CC_CALLBACK_1(VideoAdScene::menuShowRewardAdCallback, this)));
    _rewardStatus = MenuItemLabel::create(Label::createWithSystemFont("...", font, fontSize));
    rewardMenuItems.pushBack(_rewardStatus);

    auto rewardMenus = Menu::createWithArray(rewardMenuItems);
    rewardMenus->setPosition(Point(visibleSize.width * 1/ 4 + origin.x, visibleSize.height / 2 + origin.y));
    rewardMenus->alignItemsVerticallyWithPadding(36.0f);
    this->addChild(rewardMenus);
    
    Vector<MenuItem *> interstitialMenuItems;
    interstitialMenuItems.pushBack(MenuItemLabel::create(Label::createWithSystemFont("Interstitial Video", font, fontSize)));
    interstitialMenuItems.pushBack(MenuItemLabel::create(Label::createWithSystemFont("LoadAd", font, fontSize), CC_CALLBACK_1(VideoAdScene::menuLoadInterstitialAdCallback, this)));
    interstitialMenuItems.pushBack(MenuItemLabel::create(Label::createWithSystemFont("ShowAd", font, fontSize), CC_CALLBACK_1(VideoAdScene::menuShowInterstitialAdCallback, this)));
    _interstitialStatus = MenuItemLabel::create(Label::createWithSystemFont("...", font, fontSize));
    interstitialMenuItems.pushBack(_interstitialStatus);
    
    auto interstitialMenus = Menu::createWithArray(interstitialMenuItems);
    interstitialMenus->setPosition(Point(visibleSize.width * 3 / 4 + origin.x, visibleSize.height / 2 + origin.y));
    interstitialMenus->alignItemsVerticallyWithPadding(36.0f);
    this->addChild(interstitialMenus);


    // Create rewardedVideoAd instance
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    _rewardedVideoAd.reset(VideoAds::createRewardedVideoAd("802558", "a6eb8828d64c70630fd6737bd266756c5c7d48aa"));
#else
    _rewardedVideoAd.reset(VideoAds::createRewardedVideoAd("802555", "ca80ed7018734d16787dbda24c9edd26c84c15b8"));
#endif

    // Set User ID
    _rewardedVideoAd->setUserid("user id");

    // Set User Feature
    NendUserFeature *rewardedUserFeature = new NendUserFeature();
    rewardedUserFeature->setGender(NendUserFeature::Gender::FEMALE);
    rewardedUserFeature->setBirthday(2000, 1, 1);
    rewardedUserFeature->setAge(18);
    rewardedUserFeature->addCustomValue(100, "intParameter");
    rewardedUserFeature->addCustomValue(123.45, "doubleParameter");
    rewardedUserFeature->addCustomValue("test", "stringParameter");
    rewardedUserFeature->addCustomValue(true, "boolParameter");
    _rewardedVideoAd->setUserFeature(rewardedUserFeature);
    delete rewardedUserFeature;

    // Regist rewardedVideoAd callbacks
    _rewardedVideoAd->onLoaded([=](const VideoAds::RewardedVideoAd& ad) {
        Director::getInstance()->getScheduler()->performFunctionInCocosThread([=](){
            _rewardStatus->setString("Loaded");
        });
        CCLOG("RewardedVideoAd - OnLoaded.");
    });
    _rewardedVideoAd->onFailedToLoad([=](const VideoAds::RewardedVideoAd& ad, int errorCode) {
        Director::getInstance()->getScheduler()->performFunctionInCocosThread([=](){
            _rewardStatus->setString("Failed");
        });
        CCLOG("RewardedVideoAd - onFailedToLoad: %d", errorCode);
    });
    _rewardedVideoAd->onShown([](const VideoAds::RewardedVideoAd& ad) {
        CCLOG("RewardedVideoAd - onShown.");
    });
    _rewardedVideoAd->onStarted([](const VideoAds::RewardedVideoAd& ad) {
        CCLOG("RewardedVideoAd - onStarted.");
    });
    _rewardedVideoAd->onStopped([](const VideoAds::RewardedVideoAd& ad) {
        CCLOG("RewardedVideoAd - onStopped.");
    });
    _rewardedVideoAd->onCompleted([](const VideoAds::RewardedVideoAd& ad) {
        CCLOG("RewardedVideoAd - onCompleted.");
    });
    _rewardedVideoAd->onClosed([=](const VideoAds::RewardedVideoAd& ad) {
        Director::getInstance()->getScheduler()->performFunctionInCocosThread([=](){
            _rewardStatus->setString("...");
        });
        CCLOG("RewardedVideoAd - onClosed.");
    });
    _rewardedVideoAd->onAdClicked([](const VideoAds::RewardedVideoAd& ad) {
        CCLOG("RewardedVideoAd - onAdClicked.");
    });
    _rewardedVideoAd->onInformationClicked([](const VideoAds::RewardedVideoAd& ad) {
        CCLOG("RewardedVideoAd - onInformationClicked.");
    });
    _rewardedVideoAd->onFailedToPlay([](const VideoAds::RewardedVideoAd& ad) {
        CCLOG("RewardedVideoAd - onFailedToPlay.");
    });
    _rewardedVideoAd->onRewarded([](const VideoAds::RewardedVideoAd& ad, const RewardItem& item) {
        CCLOG("RewardedVideoAd - OnRewarded. %s, %d", item.getName().c_str(), item.getAmount());
    });


    // Create interstitialVideoAd
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    _interstitialVideoAd.reset(VideoAds::createInterstitialVideoAd("802559", "e9527a2ac8d1f39a667dfe0f7c169513b090ad44"));
#else
    _interstitialVideoAd.reset(VideoAds::createInterstitialVideoAd("802557", "b6a97b05dd088b67f68fe6f155fb3091f302b48b"));
#endif

    // Set User ID
    _interstitialVideoAd->setUserid("user id");

    // Set User Feature
    NendUserFeature *interstitialUserFeature = new NendUserFeature();
    interstitialUserFeature->setGender(NendUserFeature::Gender::FEMALE);
    interstitialUserFeature->setBirthday(2000, 1, 1);
    interstitialUserFeature->setAge(18);
    interstitialUserFeature->addCustomValue(100, "intParameter");
    interstitialUserFeature->addCustomValue(123.45, "doubleParameter");
    interstitialUserFeature->addCustomValue("test", "stringParameter");
    interstitialUserFeature->addCustomValue(true, "boolParameter");
    _interstitialVideoAd->setUserFeature(interstitialUserFeature);
    delete interstitialUserFeature;
    
    // Set Fallback Fullboard Ad
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    _interstitialVideoAd->addFallbackFullBoard("485520", "a88c0bcaa2646c4ef8b2b656fd38d6785762f2ff");
#else
    _interstitialVideoAd->addFallbackFullBoard("485504", "30fda4b3386e793a14b27bedb4dcd29f03d638e5");
#endif
    
    // Regist interstitialVideoAd callbacks
    _interstitialVideoAd->onLoaded([=](const VideoAds::InterstitialVideoAd& ad) {
        Director::getInstance()->getScheduler()->performFunctionInCocosThread([=](){
            _interstitialStatus->setString("Loaded");
        });
        CCLOG("InterstitialVideoAd - OnLoaded.");
    });
    _interstitialVideoAd->onFailedToLoad([=](const VideoAds::InterstitialVideoAd& ad, int errorCode) {
        Director::getInstance()->getScheduler()->performFunctionInCocosThread([=](){
            _interstitialStatus->setString("Failed");
        });
        CCLOG("InterstitialVideoAd - onFailedToLoad: %d", errorCode);
    });
    _interstitialVideoAd->onShown([](const VideoAds::InterstitialVideoAd& ad) {
        CCLOG("InterstitialVideoAd - onShown.");
    });
    _interstitialVideoAd->onStarted([](const VideoAds::InterstitialVideoAd& ad) {
        CCLOG("InterstitialVideoAd - onStarted.");
    });
    _interstitialVideoAd->onStopped([](const VideoAds::InterstitialVideoAd& ad) {
        CCLOG("InterstitialVideoAd - onStopped.");
    });
    _interstitialVideoAd->onCompleted([](const VideoAds::InterstitialVideoAd& ad) {
        CCLOG("InterstitialVideoAd - onCompleted.");
    });
    _interstitialVideoAd->onClosed([=](const VideoAds::InterstitialVideoAd& ad) {
        Director::getInstance()->getScheduler()->performFunctionInCocosThread([=](){
            _interstitialStatus->setString("...");
        });
        CCLOG("InterstitialVideoAd - onClosed.");
    });
    _interstitialVideoAd->onAdClicked([](const VideoAds::InterstitialVideoAd& ad) {
        CCLOG("InterstitialVideoAd - onAdClicked.");
    });
    _interstitialVideoAd->onInformationClicked([](const VideoAds::InterstitialVideoAd& ad) {
        CCLOG("InterstitialVideoAd - onInformationClicked.");
    });
    _interstitialVideoAd->onFailedToPlay([](const VideoAds::InterstitialVideoAd& ad) {
        CCLOG("InterstitialVideoAd - onFailedToPlay.");
    });

    
    return true;
}

void VideoAdScene::menuLoadRewardAdCallback(Ref *pSender)
{
    _rewardStatus->setString("Loading...");
    _rewardedVideoAd->loadAd();
}

void VideoAdScene::menuShowRewardAdCallback(Ref *pSender)
{
    if (_rewardedVideoAd->isReady()) {
        _rewardedVideoAd->showAd();
    }
}

void VideoAdScene::menuLoadInterstitialAdCallback(Ref *pSender)
{
    _interstitialStatus->setString("Loading...");
    _interstitialVideoAd->loadAd();
}

void VideoAdScene::menuShowInterstitialAdCallback(Ref *pSender)
{
    if (_interstitialVideoAd->isReady()) {
        _interstitialVideoAd->showAd();
    }
}

void VideoAdScene::showPreviousSceneButtonCallback(Ref* pSender)
{
    Director::getInstance()->replaceScene(TransitionSlideInL::create(0.5f,HelloWorld::createScene()));
}

//
//  FullBoardAdScene.cpp
//  CocosNendSample
//

#include "FullBoardAdScene.h"

#include "cocos2d.h"
#include "HelloWorldScene.h"

USING_NS_CC;

Scene* FullBoardAdScene::createScene()
{
    return FullBoardAdScene::create();
}

bool FullBoardAdScene::init()
{
    //////////////////////////////
    // 1. super init first
    if (!Scene::init())
    {
        return false;
    }
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.
    
    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(FullBoardAdScene::menuCloseCallback, this));
    
    closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));
    
    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
    
    /////////////////////////////
    // 3. add your codes below...
    
    auto label = Label::createWithTTF("FullBoardAd", "fonts/Marker Felt.ttf", 24);
    
    // position the label on the center of the screen
    label->setPosition(Point(origin.x + visibleSize.width/2,
                             origin.y + visibleSize.height - label->getContentSize().height));
    
    // add the label as a child to this layer
    this->addChild(label, 1);
    
    const std::string font = StringUtils::format("fonts/arial.ttf");
    const float fontSize = 15.0f;
    
    Vector<MenuItem *> vec;
    vec.pushBack(MenuItemLabel::create(Label::createWithSystemFont("LoadAd", font, fontSize), CC_CALLBACK_1(FullBoardAdScene::menuLoadAdCallback, this)));
    vec.pushBack(MenuItemLabel::create(Label::createWithSystemFont("ShowAd", font, fontSize), CC_CALLBACK_1(FullBoardAdScene::menuShowAdCallback, this)));
    _status = MenuItemLabel::create(Label::createWithSystemFont("...", font, fontSize));
    vec.pushBack(_status);
    
    auto menus = Menu::createWithArray(vec);
    menus->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    menus->alignItemsVerticallyWithPadding(36.0f);
    this->addChild(menus);
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    _ad = new nend_module::NendFullBoardAd("485520", "a88c0bcaa2646c4ef8b2b656fd38d6785762f2ff");
#else
    _ad = new nend_module::NendFullBoardAd("485504", "30fda4b3386e793a14b27bedb4dcd29f03d638e5");
#endif
    _ad->setBackgroundColor4F(cocos2d::Color4F::WHITE);
    
    _ad->onFullBoardAdLoaded = [this](const nend_module::NendFullBoardAd& ad) {
        log("onFullBoardAdLoaded");
        _status->setString("Success");
    };
    _ad->onFullBoardAdFailedToLoad = [this](const nend_module::NendFullBoardAd& ad, const nend_module::NendFullBoardAd::ErrorType error) {
        log("onFullBoardAdFailedToLoad : error type");
        switch (error) {
            case nend_module::NendFullBoardAd::ErrorType::FAILED_TO_AD_REQUEST:
                _status->setString("Failed to ad request.");
                break;
            case nend_module::NendFullBoardAd::ErrorType::FAILED_TO_DOWNLOAD_IMAGE:
                _status->setString("Failed to download image.");
                break;
            case nend_module::NendFullBoardAd::ErrorType::INVALID_AD_SPACES:
                _status->setString("Invalid ad spaces specified.");
                break;
            default:
                break;
        }
    };
    _ad->onFullBoardAdShown = [this](const nend_module::NendFullBoardAd& ad) {
        log("onFullBoardAdShown");
    };
    _ad->onFullBoardAdDismissed = [this](const nend_module::NendFullBoardAd& ad) {
        log("onFullBoardAdDismissed");
        this->menuLoadAdCallback(NULL);
    };
    _ad->onFullBoardAdClicked = [this](const nend_module::NendFullBoardAd& ad) {
        log("onFullBoardAdClicked");
    };
    return true;
}

void FullBoardAdScene::menuLoadAdCallback(Ref *pSender)
{
    _status->setString("Loading...");
    _ad->load();
}

void FullBoardAdScene::menuShowAdCallback(Ref *pSender)
{
    _ad->show();
}

void FullBoardAdScene::menuCloseCallback(Ref *pSender)
{
    Director::getInstance()->replaceScene(TransitionSlideInL::create(0.5f, HelloWorld::createScene()));
}


//
//  BannerViewScene.cpp
//  HelloCpp
//
//  Created by F@N Communications, Inc.
//
//

#include "BannerViewScene.h"
#include "BannerMenuScene.h"
#include "NendModule.h"
#include "string.h"

USING_NS_CC;

BannerSize adSize;
bool isAdjustFlag;
char apiKey[256];
char spotID[128];

Scene* BannerViewScene::createScene(BannerSize bannerSize)
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = BannerViewScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    adSize = bannerSize;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    switch (adSize) {
        case BANNER_320_50:
            strcpy(apiKey,"a6eca9dd074372c898dd1df549301f277c53f2b9");
            strcpy(spotID,"3172");
            break;
        case BANNER_320_100:
            strcpy(apiKey,"eb5ca11fa8e46315c2df1b8e283149049e8d235e");
            strcpy(spotID,"70996");
            break;
        case BANNER_300_100:
            strcpy(apiKey,"25eb32adddc4f7311c3ec7b28eac3b72bbca5656");
            strcpy(spotID,"70998");
            break;
        case BANNER_300_250:
            strcpy(apiKey,"88d88a288fdea5c01d17ea8e494168e834860fd6");
            strcpy(spotID,"70356");
            break;
        case BANNER_728_90:
            strcpy(apiKey,"2e0b9e0b3f40d952e6000f1a8c4d455fffc4ca3a");
            strcpy(spotID,"70999");
            break;
        default:
            break;
    }
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    switch (adSize) {
        case BANNER_320_50:
            strcpy(apiKey,"c5cb8bc474345961c6e7a9778c947957ed8e1e4f");
            strcpy(spotID,"3174");
            break;
        case BANNER_320_100:
            strcpy(apiKey,"8932b68d22d1d32f5d7251f9897a6aa64117995e");
            strcpy(spotID,"71000");
            break;
        case BANNER_300_100:
            strcpy(apiKey,"1e36d1183d1ab66539998df4170a591c13028416");
            strcpy(spotID,"71001");
            break;
        case BANNER_300_250:
            strcpy(apiKey,"499f011dbec5d37cfa388b749aed2bfff440a794");
            strcpy(spotID,"70357");
            break;
        case BANNER_728_90:
            strcpy(apiKey,"02e6e186bf0183105fba7ce310dafe68ac83fb1c");
            strcpy(spotID,"71002");
            break;
        default:
            break;
    }
#endif

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool BannerViewScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();
    
    isAdjustFlag = false;
    
    /////////////////////////////
    // 3. add your codes below...
    
    // add a label shows "Hello World"
    // create and initialize a label
    
    auto director = Director::getInstance();
    auto displayScale = director->getContentScaleFactor();
    
    auto font = String::create("fonts/arial.ttf");
    auto fontSize = 15 * displayScale;
    
    auto label = Label::createWithTTF("BannerViewScene", "fonts/Marker Felt.ttf", 24 * displayScale);
    
    // position the label on the center of the screen
    label->setPosition(Point(origin.x + visibleSize.width/2,
                             origin.y + visibleSize.height - label->getContentSize().height));
    
    // add the label as a child to this layer
    this->addChild(label, 1);
    
    auto createBannerTopLabel = Label::createWithSystemFont("createTop", font->getCString(), fontSize);
    auto createBannerTopItem = MenuItemLabel::create(createBannerTopLabel, CC_CALLBACK_1(BannerViewScene::createBannerTopCallback, this));
    auto createBannerTopMenu = Menu::create(createBannerTopItem, NULL);
    createBannerTopMenu->setPosition(Point(visibleSize.width/2 + origin.x - 100 * displayScale, visibleSize.height/2 + origin.y + 150 * displayScale));
    this->addChild(createBannerTopMenu);
    
    auto createBannerBottomLabel = Label::createWithSystemFont("createBottom", font->getCString(), fontSize);
    auto createBannerBottomItem = MenuItemLabel::create(createBannerBottomLabel, CC_CALLBACK_1(BannerViewScene::createBannerBottomCallback, this));
    auto createBannerBottomMenu = Menu::create(createBannerBottomItem, NULL);
    createBannerBottomMenu->setPosition(Point(visibleSize.width/2 + origin.x + 100 * displayScale, visibleSize.height/2 + origin.y + 150 * displayScale));
    this->addChild(createBannerBottomMenu);
    
    auto createBannerUserLabel = Label::createWithSystemFont("createUser", font->getCString(), fontSize);
    auto createBannerUserItem = MenuItemLabel::create(createBannerUserLabel, CC_CALLBACK_1(BannerViewScene::createBannerUserCallback, this));
    auto createBannerUserMenu = Menu::create(createBannerUserItem, NULL);
    createBannerUserMenu->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y + 150 * displayScale));
    this->addChild(createBannerUserMenu);
    
    auto showBannerLabel = Label::createWithSystemFont("show", font->getCString(), fontSize);
    auto showBannerItem = MenuItemLabel::create(showBannerLabel, CC_CALLBACK_1(BannerViewScene::showBannerCallback, this));
    auto showBannerMenu = Menu::create(showBannerItem, NULL);
    showBannerMenu->setPosition(Point(visibleSize.width/2 + origin.x - 100 * displayScale, visibleSize.height/2 + origin.y + 100 * displayScale));
    this->addChild(showBannerMenu);

    auto hideBannerLabel = Label::createWithSystemFont("hide", font->getCString(), fontSize);
    auto hideBannerItem = MenuItemLabel::create(hideBannerLabel, CC_CALLBACK_1(BannerViewScene::hideBannerCallback, this));
    auto hideBannerMenu = Menu::create(hideBannerItem, NULL);
    hideBannerMenu->setPosition(Point(visibleSize.width/2 + origin.x + 100 * displayScale, visibleSize.height/2 + origin.y + 100 * displayScale));
    this->addChild(hideBannerMenu);

    auto pauseBannerLabel = Label::createWithSystemFont("pause", font->getCString(), fontSize);
    auto pauseBannerItem = MenuItemLabel::create(pauseBannerLabel, CC_CALLBACK_1(BannerViewScene::pauseBannerCallback, this));
    auto pauseBannerMenu = Menu::create(pauseBannerItem, NULL);
    pauseBannerMenu->setPosition(Point(visibleSize.width/2 + origin.x - 100 * displayScale, visibleSize.height/2 + origin.y + 50 * displayScale));
    this->addChild(pauseBannerMenu);

    auto resumeBannerLabel = Label::createWithSystemFont("resume", font->getCString(), fontSize);
    auto resumeBannerItem = MenuItemLabel::create(resumeBannerLabel, CC_CALLBACK_1(BannerViewScene::resumeBannerCallback, this));
    auto resumeBannerMenu = Menu::create(resumeBannerItem, NULL);
    resumeBannerMenu->setPosition(Point(visibleSize.width/2 + origin.x + 100 * displayScale, visibleSize.height/2 + origin.y + 50 * displayScale));
    this->addChild(resumeBannerMenu);

    auto releaseBannerLabel = Label::createWithSystemFont("release", font->getCString(), fontSize);
    auto releaseBannerItem = MenuItemLabel::create(releaseBannerLabel, CC_CALLBACK_1(BannerViewScene::releaseBannerCallback, this));
    auto releaseBannerMenu = Menu::create(releaseBannerItem, NULL);
    releaseBannerMenu->setPosition(Point(visibleSize.width/2 + origin.x - 100 * displayScale, visibleSize.height/2 + origin.y));
    this->addChild(releaseBannerMenu);
    
    auto adjustOnLabel = Label::createWithSystemFont("AdjustON", font->getCString(), fontSize);
    auto adjustOnItem = MenuItemLabel::create(adjustOnLabel, CC_CALLBACK_1(BannerViewScene::isAdjustOnCallback, this));
    auto adjustOnMenu = Menu::create(adjustOnItem, NULL);
    adjustOnMenu->setPosition(Point(visibleSize.width/2 + origin.x - 100 * displayScale, visibleSize.height/2 + origin.y - 150 * displayScale));
    this->addChild(adjustOnMenu);
    
    auto adjustOffLabel = Label::createWithSystemFont("AdjustOFF", font->getCString(), fontSize);
    auto adjustOffItem = MenuItemLabel::create(adjustOffLabel, CC_CALLBACK_1(BannerViewScene::isAdjustOffCallback, this));
    auto adjustOffMenu = Menu::create(adjustOffItem, NULL);
    adjustOffMenu->setPosition(Point(visibleSize.width/2 + origin.x + 100 * displayScale, visibleSize.height/2 + origin.y - 150 * displayScale));
    this->addChild(adjustOffMenu);
    
    auto showPreviousLabel = Label::createWithSystemFont("Back", font->getCString(), fontSize);
    auto showPreviousItem = MenuItemLabel::create(showPreviousLabel, CC_CALLBACK_1(BannerViewScene::showPreviousSceneButtonCallback, this));
    auto showPreviousMenu = Menu::create(showPreviousItem, NULL);
    showPreviousMenu->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y - 150 * displayScale));
    this->addChild(showPreviousMenu);
    
    // EventDispatcher登録
    this->addEventDispatcher();
    
    return true;
}

void BannerViewScene::onEnter()
{
    CCLayer::onEnter();
}

void BannerViewScene::onExit()
{
    CCLayer::onExit();

    // バナー広告のリソースを解放する
    NendModule::release();
    // EventDispatcher登録の解除
    this->removeEventDispatcher();
}

void BannerViewScene::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    
#endif
}

#pragma mark - メニューボタンのコールバック
// 画面上部中央に広告を表示する
void BannerViewScene::createBannerTopCallback(cocos2d::Ref* pSender)
{
    NendModule::createNADViewTop(apiKey, spotID, isAdjustFlag);
}
// 画面下部中央に広告を表示する
void BannerViewScene::createBannerBottomCallback(cocos2d::Ref* pSender)
{
    NendModule::createNADViewBottom(apiKey, spotID, isAdjustFlag);
}
// 位置を指定して広告を表示する
void BannerViewScene::createBannerUserCallback(cocos2d::Ref* pSender)
{
    NendModule::createNADView(apiKey, spotID, Point(50, 200), isAdjustFlag);
}
// バナー広告を表示する
void BannerViewScene::showBannerCallback(cocos2d::Ref* pSender)
{
    NendModule::showNADView();
}
// バナー広告を非表示にする
void BannerViewScene::hideBannerCallback(cocos2d::Ref* pSender)
{
    NendModule::hideNADView();
}
// バナー広告のロードを一時停止する
void BannerViewScene::pauseBannerCallback(cocos2d::Ref* pSender)
{
    NendModule::pause();
}
// バナー広告のロードを再開する
void BannerViewScene::resumeBannerCallback(cocos2d::Ref* pSender)
{
    NendModule::resume();
}
// バナー広告のリソースを解放する
void BannerViewScene::releaseBannerCallback(cocos2d::Ref* pSender)
{
    NendModule::release();
}
// バナーサイズの自動調整をONにする
void BannerViewScene::isAdjustOnCallback(cocos2d::Ref* pSender)
{
    isAdjustFlag = true;
}
// バナーサイズの自動調整をOFFにする
void BannerViewScene::isAdjustOffCallback(cocos2d::Ref* pSender)
{
    isAdjustFlag = false;
}
// 前の画面に遷移する
void BannerViewScene::showPreviousSceneButtonCallback(Ref* pSender)
{
    Director::getInstance()->replaceScene(TransitionSlideInL::create(0.5f,BannerMenuScene::createScene()));
}


#pragma mark - EventDispatcher登録
void BannerViewScene::addEventDispatcher()
{
    // EventDispatcherで通知を受け取る
    Director::getInstance()->getEventDispatcher()->addCustomEventListener(NADViewDelegateNotification,[&](cocos2d::EventCustom *event) {
        int *intValue = (int *)event->getUserData();
        int resultCode = *intValue;
        switch (resultCode) {
            case FINISH_LOAD_AD:      // iOSのみ
                // 広告ロード完了
                log("FINISH_LOAD_AD");
                break;
            case RECEIVE_AD:
                // 広告受信成功
                log("RECEIVE_AD");
                break;
            case FAIL_TO_RECEIVE_AD:
                // 広告受信失敗
                log("FAIL_TO_RECEIVE_AD");
                break;
            case CLICK_AD:
                // バナー広告クリック
                log("CLICK_AD");
                break;
            default:
                break;
        }
    });
}

#pragma mark - EventDispatcher登録の解除
void BannerViewScene::removeEventDispatcher()
{
    // EventDispatcherの通知を停止
    Director::getInstance()->getEventDispatcher()->removeCustomEventListeners(NADViewDelegateNotification);
}

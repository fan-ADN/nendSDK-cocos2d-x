//
//  BannerViewWithSpotIDScene.cpp
//  CocosNendSample
//
//  Created by F@N Communications, Inc.
//
//

#include "BannerViewWithSpotIDScene.h"
#include "NendModule.h"
#include "string.h"
#include "HelloWorldScene.h"

USING_NS_CC;

bool _isAdjustFlag;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)

// 広告枠AのapiKeyとspotID (バナーサイズ：320x50)
static char apiKey_A[] = "a6eca9dd074372c898dd1df549301f277c53f2b9";
static char spotID_A[] = "3172";

// 広告枠BのapiKeyとspotID (バナーサイズ：320x100)
static char apiKey_B[] = "eb5ca11fa8e46315c2df1b8e283149049e8d235e";
static char spotID_B[] = "70996";

#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

// 広告枠AのapiKeyとspotID (バナーサイズ：320x50)
static char apiKey_A[] = "c5cb8bc474345961c6e7a9778c947957ed8e1e4f";
static char spotID_A[] = "3174";

// 広告枠BのapiKeyとspotID (バナーサイズ：320x100)
static char apiKey_B[] = "8932b68d22d1d32f5d7251f9897a6aa64117995e";
static char spotID_B[] = "71000";

#endif

Scene* BannerViewWithSpotIDScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = BannerViewWithSpotIDScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool BannerViewWithSpotIDScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();
    
    _isAdjustFlag = false;
    
    /////////////////////////////
    // 3. add your codes below...
    
    // add a label shows "Hello World"
    // create and initialize a label
    
    auto director = Director::getInstance();
    
    std::string font = StringUtils::format("fonts/arial.ttf");
    auto fontSize = 15;
    
    auto label = Label::createWithTTF("BannerViewWithSpotIDScene", "fonts/Marker Felt.ttf", 24);
    
    // position the label on the center of the screen
    label->setPosition(Point(origin.x + visibleSize.width/2,
                             origin.y + visibleSize.height - label->getContentSize().height));
    
    // add the label as a child to this layer
    this->addChild(label, 1);
    
    auto createBannerTopLabel = Label::createWithSystemFont("createTop_A", font, fontSize);
    auto createBannerTopItem = MenuItemLabel::create(createBannerTopLabel, CC_CALLBACK_1(BannerViewWithSpotIDScene::createBannerTopCallback, this));
    auto createBannerTopMenu = Menu::create(createBannerTopItem, NULL);
    createBannerTopMenu->setPosition(Point(visibleSize.width/2 + origin.x - 110, visibleSize.height/2 + origin.y + 150));
    this->addChild(createBannerTopMenu);
    
    auto createBannerBottomLabel = Label::createWithSystemFont("createBottom_B", font, fontSize);
    auto createBannerBottomItem = MenuItemLabel::create(createBannerBottomLabel, CC_CALLBACK_1(BannerViewWithSpotIDScene::createBannerBottomCallback, this));
    auto createBannerBottomMenu = Menu::create(createBannerBottomItem, NULL);
    createBannerBottomMenu->setPosition(Point(visibleSize.width/2 + origin.x + 110, visibleSize.height/2 + origin.y + 150));
    this->addChild(createBannerBottomMenu);
    
    auto createBannerUserLabel = Label::createWithSystemFont("createUser_A", font, fontSize);
    auto createBannerUserItem = MenuItemLabel::create(createBannerUserLabel, CC_CALLBACK_1(BannerViewWithSpotIDScene::createBannerUserCallback, this));
    auto createBannerUserMenu = Menu::create(createBannerUserItem, NULL);
    createBannerUserMenu->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y + 150));
    this->addChild(createBannerUserMenu);
    
    auto showBannerLabel = Label::createWithSystemFont("show_A", font, fontSize);
    auto showBannerItem = MenuItemLabel::create(showBannerLabel, CC_CALLBACK_1(BannerViewWithSpotIDScene::showBannerCallback, this));
    auto showBannerMenu = Menu::create(showBannerItem, NULL);
    showBannerMenu->setPosition(Point(visibleSize.width/2 + origin.x - 100, visibleSize.height/2 + origin.y + 100));
    this->addChild(showBannerMenu);
    
    auto showBannerWithSpotIDLabel = Label::createWithSystemFont("show_B", font, fontSize);
    auto showBannerWithSpotIDItem = MenuItemLabel::create(showBannerWithSpotIDLabel, CC_CALLBACK_1(BannerViewWithSpotIDScene::showBannerWithSpotIDCallback, this));
    auto showBannerWithSpotIDMenu = Menu::create(showBannerWithSpotIDItem, NULL);
    showBannerWithSpotIDMenu->setPosition(Point(visibleSize.width/2 + origin.x + 100, visibleSize.height/2 + origin.y + 100));
    this->addChild(showBannerWithSpotIDMenu);
    
    auto hideBannerLabel = Label::createWithSystemFont("hide_A", font, fontSize);
    auto hideBannerItem = MenuItemLabel::create(hideBannerLabel, CC_CALLBACK_1(BannerViewWithSpotIDScene::hideBannerCallback, this));
    auto hideBannerMenu = Menu::create(hideBannerItem, NULL);
    hideBannerMenu->setPosition(Point(visibleSize.width/2 + origin.x - 100, visibleSize.height/2 + origin.y + 50));
    this->addChild(hideBannerMenu);
    
    auto hideBannerWithSpotIDLabel = Label::createWithSystemFont("hide_B", font, fontSize);
    auto hideBannerWithSpotIDItem = MenuItemLabel::create(hideBannerWithSpotIDLabel, CC_CALLBACK_1(BannerViewWithSpotIDScene::hideBannerWithSpotIDCallback, this));
    auto hideBannerWithSpotIDMenu = Menu::create(hideBannerWithSpotIDItem, NULL);
    hideBannerWithSpotIDMenu->setPosition(Point(visibleSize.width/2 + origin.x + 100, visibleSize.height/2 + origin.y + 50));
    this->addChild(hideBannerWithSpotIDMenu);
    
    auto pauseBannerLabel = Label::createWithSystemFont("pause_A", font, fontSize);
    auto pauseBannerItem = MenuItemLabel::create(pauseBannerLabel, CC_CALLBACK_1(BannerViewWithSpotIDScene::pauseBannerCallback, this));
    auto pauseBannerMenu = Menu::create(pauseBannerItem, NULL);
    pauseBannerMenu->setPosition(Point(visibleSize.width/2 + origin.x - 100, visibleSize.height/2 + origin.y));
    this->addChild(pauseBannerMenu);
    
    auto pauseBannerWithSpotIDLabel = Label::createWithSystemFont("pause_B", font, fontSize);
    auto pauseBannerWithSpotIDItem = MenuItemLabel::create(pauseBannerWithSpotIDLabel, CC_CALLBACK_1(BannerViewWithSpotIDScene::pauseBannerWithSpotIDCallback, this));
    auto pauseBannerWithSpotIDMenu = Menu::create(pauseBannerWithSpotIDItem, NULL);
    pauseBannerWithSpotIDMenu->setPosition(Point(visibleSize.width/2 + origin.x + 100, visibleSize.height/2 + origin.y));
    this->addChild(pauseBannerWithSpotIDMenu);
    
    auto resumeBannerLabel = Label::createWithSystemFont("resume_A", font, fontSize);
    auto resumeBannerItem = MenuItemLabel::create(resumeBannerLabel, CC_CALLBACK_1(BannerViewWithSpotIDScene::resumeBannerCallback, this));
    auto resumeBannerMenu = Menu::create(resumeBannerItem, NULL);
    resumeBannerMenu->setPosition(Point(visibleSize.width/2 + origin.x - 100, visibleSize.height/2 + origin.y - 50));
    this->addChild(resumeBannerMenu);
    
    auto resumeBannerWithSpotIDLabel = Label::createWithSystemFont("resume_B", font, fontSize);
    auto resumeBannerWithSpotIDItem = MenuItemLabel::create(resumeBannerWithSpotIDLabel, CC_CALLBACK_1(BannerViewWithSpotIDScene::resumeBannerWithSpotIDCallback, this));
    auto resumeBannerWithSpotIDMenu = Menu::create(resumeBannerWithSpotIDItem, NULL);
    resumeBannerWithSpotIDMenu->setPosition(Point(visibleSize.width/2 + origin.x + 100, visibleSize.height/2 + origin.y - 50));
    this->addChild(resumeBannerWithSpotIDMenu);
    
    auto releaseBannerLabel = Label::createWithSystemFont("release_A", font, fontSize);
    auto releaseBannerItem = MenuItemLabel::create(releaseBannerLabel, CC_CALLBACK_1(BannerViewWithSpotIDScene::releaseBannerCallback, this));
    auto releaseBannerMenu = Menu::create(releaseBannerItem, NULL);
    releaseBannerMenu->setPosition(Point(visibleSize.width/2 + origin.x - 100, visibleSize.height/2 + origin.y - 100));
    this->addChild(releaseBannerMenu);
    
    auto releaseBannerWithSpotIDLabel = Label::createWithSystemFont("release_B", font, fontSize);
    auto releaseBannerWithSpotIDItem = MenuItemLabel::create(releaseBannerWithSpotIDLabel, CC_CALLBACK_1(BannerViewWithSpotIDScene::releaseBannerWithSpotIDCallback, this));
    auto releaseBannerWithSpotIDMenu = Menu::create(releaseBannerWithSpotIDItem, NULL);
    releaseBannerWithSpotIDMenu->setPosition(Point(visibleSize.width/2 + origin.x + 100, visibleSize.height/2 + origin.y - 100));
    this->addChild(releaseBannerWithSpotIDMenu);
    
    auto adjustOnLabel = Label::createWithSystemFont("AdjustON", font, fontSize);
    auto adjustOnItem = MenuItemLabel::create(adjustOnLabel, CC_CALLBACK_1(BannerViewWithSpotIDScene::isAdjustOnCallback, this));
    auto adjustOnMenu = Menu::create(adjustOnItem, NULL);
    adjustOnMenu->setPosition(Point(visibleSize.width/2 + origin.x - 100, visibleSize.height/2 + origin.y - 150));
    this->addChild(adjustOnMenu);
    
    auto adjustOffLabel = Label::createWithSystemFont("AdjustOFF", font, fontSize);
    auto adjustOffItem = MenuItemLabel::create(adjustOffLabel, CC_CALLBACK_1(BannerViewWithSpotIDScene::isAdjustOffCallback, this));
    auto adjustOffMenu = Menu::create(adjustOffItem, NULL);
    adjustOffMenu->setPosition(Point(visibleSize.width/2 + origin.x + 100, visibleSize.height/2 + origin.y - 150));
    this->addChild(adjustOffMenu);
    
    auto showPreviousLabel = Label::createWithSystemFont("Back", font, fontSize);
    auto showPreviousItem = MenuItemLabel::create(showPreviousLabel, CC_CALLBACK_1(BannerViewWithSpotIDScene::showPreviousSceneButtonCallback, this));
    auto showPreviousMenu = Menu::create(showPreviousItem, NULL);
    showPreviousMenu->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y - 150));
    this->addChild(showPreviousMenu);
    
    // EventDispatcher登録
    this->addEventDispatcher();
    
    return true;
}

void BannerViewWithSpotIDScene::onEnter()
{
    Layer::onEnter();
}

void BannerViewWithSpotIDScene::onExit()
{
    Layer::onExit();
}

void BannerViewWithSpotIDScene::onExitTransitionDidStart()
{
    // バナー広告のリソースを解放する
    NendModule::release();
    // EventDispatcher登録の解除
    this->removeEventDispatcher();
}

void BannerViewWithSpotIDScene::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    
#endif
}

#pragma mark - メニューボタンのコールバック
// 画面上部中央に広告を表示する(広告枠A)
void BannerViewWithSpotIDScene::createBannerTopCallback(cocos2d::Ref* pSender)
{
    NendModule::createNADViewTop(apiKey_A, spotID_A, _isAdjustFlag);
}
// 画面下部中央に広告を表示する(広告枠B)
void BannerViewWithSpotIDScene::createBannerBottomCallback(cocos2d::Ref* pSender)
{
    NendModule::createNADViewBottom(apiKey_B, spotID_B, _isAdjustFlag);
}
// 位置を指定して広告を表示する(広告枠A)
void BannerViewWithSpotIDScene::createBannerUserCallback(cocos2d::Ref* pSender)
{
    NendModule::createNADView(apiKey_A, spotID_A, Point(50, 400), _isAdjustFlag);
}
// バナー広告を表示する(広告枠A)
void BannerViewWithSpotIDScene::showBannerCallback(cocos2d::Ref* pSender)
{
    NendModule::showNADView(spotID_A);
}
// バナー広告を表示する(広告枠B)
void BannerViewWithSpotIDScene::showBannerWithSpotIDCallback(cocos2d::Ref* pSender)
{
    NendModule::showNADView(spotID_B);
}
// バナー広告を非表示にする(広告枠A)
void BannerViewWithSpotIDScene::hideBannerCallback(cocos2d::Ref* pSender)
{
    NendModule::hideNADView(spotID_A);
}
// バナー広告を非表示にする(広告枠B)
void BannerViewWithSpotIDScene::hideBannerWithSpotIDCallback(cocos2d::Ref* pSender)
{
    NendModule::hideNADView(spotID_B);
}
// バナー広告のロードを一時停止する(広告枠A)
void BannerViewWithSpotIDScene::pauseBannerCallback(cocos2d::Ref* pSender)
{
    NendModule::pause(spotID_A);
}
// バナー広告のロードを一時停止する(広告枠B)
void BannerViewWithSpotIDScene::pauseBannerWithSpotIDCallback(cocos2d::Ref* pSender)
{
    NendModule::pause(spotID_B);
}
// バナー広告のロードを再開する(広告枠A)
void BannerViewWithSpotIDScene::resumeBannerCallback(cocos2d::Ref* pSender)
{
    NendModule::resume(spotID_A);
}
// バナー広告のロードを再開する(広告枠B)
void BannerViewWithSpotIDScene::resumeBannerWithSpotIDCallback(cocos2d::Ref* pSender)
{
    NendModule::resume(spotID_B);
}
// バナー広告のリソースを解放する(広告枠A)
void BannerViewWithSpotIDScene::releaseBannerCallback(cocos2d::Ref* pSender)
{
    NendModule::release(spotID_A);
}
// バナー広告のリソースを解放する(広告枠B)
void BannerViewWithSpotIDScene::releaseBannerWithSpotIDCallback(cocos2d::Ref* pSender)
{
    NendModule::release(spotID_B);
}
// バナーサイズの自動調整をONにする
void BannerViewWithSpotIDScene::isAdjustOnCallback(cocos2d::Ref* pSender)
{
    _isAdjustFlag = true;
}
// バナーサイズの自動調整をOFFにする
void BannerViewWithSpotIDScene::isAdjustOffCallback(cocos2d::Ref* pSender)
{
    _isAdjustFlag = false;
}
// 前の画面に遷移する
void BannerViewWithSpotIDScene::showPreviousSceneButtonCallback(Ref* pSender)
{
    Director::getInstance()->replaceScene(TransitionSlideInL::create(0.5f,HelloWorld::createScene()));
}


#pragma mark - EventDispatcher登録
void BannerViewWithSpotIDScene::addEventDispatcher()
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
    
    Director::getInstance()->getEventDispatcher()->addCustomEventListener(NADViewDelegateWithSpotIdNotification,[&](cocos2d::EventCustom *event) {
        int *resultArray = (int *)event->getUserData();
        int resultCode = resultArray[0];
        int spotId = resultArray[1];
        switch (resultCode) {
            case FINISH_LOAD_AD:      // iOSのみ
                // 広告ロード完了
                log("FINISH_LOAD_AD:%d",spotId);
                break;
            case RECEIVE_AD:
                // 広告受信成功
                log("RECEIVE_AD:%d",spotId);
                break;
            case FAIL_TO_RECEIVE_AD:
                // 広告受信失敗
                log("FAIL_TO_RECEIVE_AD:%d",spotId);
                break;
            case CLICK_AD:
                // バナー広告クリック
                log("CLICK_AD:%d",spotId);
                break;
            default:
                break;
        }
    });
}

#pragma mark - EventDispatcher登録の解除
void BannerViewWithSpotIDScene::removeEventDispatcher()
{
    // EventDispatcherの通知を停止
    Director::getInstance()->getEventDispatcher()->removeCustomEventListeners(NADViewDelegateNotification);
    Director::getInstance()->getEventDispatcher()->removeCustomEventListeners(NADViewDelegateWithSpotIdNotification);
}

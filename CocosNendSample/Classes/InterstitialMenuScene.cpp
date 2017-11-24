//
//  InterstitialMenuScene.cpp
//  CocosNendSample
//
//  Created by F@N Communications, Inc.
//
//

#include "InterstitialMenuScene.h"
#include "HelloWorldScene.h"
#include "NendInterstitialModule.h"

USING_NS_CC;

// 管理画面で取得したapiKeyとspotID
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
static char interstitialApiKey[] = "308c2499c75c4a192f03c02b2fcebd16dcb45cc9";
static char interstitialSpotID[] = "213208";
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
static char interstitialApiKey[] = "8c278673ac6f676dae60a1f56d16dad122e23516";
static char interstitialSpotID[] = "213206";
#endif

Scene* InterstitialMenuScene::createScene()
{
    return InterstitialMenuScene::create();
}

// on "init" you need to initialize your instance
bool InterstitialMenuScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();
    
    
    /////////////////////////////
    // 3. add your codes below...
    
    // backキーイベント検知を有効にする
    auto keyboardListener = EventListenerKeyboard::create();
    keyboardListener->onKeyReleased = CC_CALLBACK_2(InterstitialMenuScene::onKeyReleased, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyboardListener, this);
    
    // add a label shows "Hello World"
    // create and initialize a label
    
    std::string font = StringUtils::format("fonts/arial.ttf");
    auto fontSize = 15;
    
    auto label = Label::createWithTTF("InterstitialMenuScene", "fonts/Marker Felt.ttf", 24);
    
    // position the label on the center of the screen
    label->setPosition(Point(origin.x + visibleSize.width/2,
                             origin.y + visibleSize.height - label->getContentSize().height));
    
    // add the label as a child to this layer
    this->addChild(label, 1);
    
    auto showLabel = Label::createWithSystemFont("Show", font, fontSize);
    auto showItem = MenuItemLabel::create(showLabel, CC_CALLBACK_1(InterstitialMenuScene::showInterstitialButtonCallback, this));
    auto showMenu = Menu::create(showItem, NULL);
    showMenu->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y + 100));
    this->addChild(showMenu);
    
    auto showInterstitialLabel = Label::createWithSystemFont("ShowWithSpotID", font, fontSize);
    auto showInterstitialItem = MenuItemLabel::create(showInterstitialLabel, CC_CALLBACK_1(InterstitialMenuScene::showInterstitialWithSpotIdButtonCallback, this));
    auto showInterstitialMenu = Menu::create(showInterstitialItem, NULL);
    showInterstitialMenu->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y + 50));
    this->addChild(showInterstitialMenu);
    
    auto hideInterstitialLabel = Label::createWithSystemFont("dismiss", font, fontSize);
    auto hideInterstitialItem = MenuItemLabel::create(hideInterstitialLabel, CC_CALLBACK_1(InterstitialMenuScene::hideInterstitialWithSpotIdButtonCallback, this));
    auto hideInterstitialMenu = Menu::create(hideInterstitialItem, NULL);
    hideInterstitialMenu->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    this->addChild(hideInterstitialMenu);
    
    auto showPreviousLabel = Label::createWithSystemFont("Back", font, fontSize);
    auto showPreviousItem = MenuItemLabel::create(showPreviousLabel, CC_CALLBACK_1(InterstitialMenuScene::showPreviousSceneButtonCallback, this));
    auto showPreviousMenu = Menu::create(showPreviousItem, NULL);
    showPreviousMenu->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y - 150));
    this->addChild(showPreviousMenu);
    
    // EventDispatcher登録
    this->addEventDispatcher();
    
    NendInterstitialModule::setEnableAutoReload(true);
    
    return true;
}

void InterstitialMenuScene::onEnter()
{
    Scene::onEnter();
    
    // インタースティシャル広告のロードを開始する
    NendInterstitialModule::createNADInterstitial(interstitialApiKey, interstitialSpotID);
    
}

void InterstitialMenuScene::onExit()
{
    Scene::onExit();
    // EventDispatcher登録の解除
    this->removeEventDispatcher();
}

void InterstitialMenuScene::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    
#endif
}

#pragma mark - メニューボタンのコールバック
// インタースティシャル広告を表示する
void InterstitialMenuScene::showInterstitialButtonCallback(cocos2d::Ref* pSender)
{
    NendInterstitialModule::showNADInterstitialView();
}
// インタースティシャル広告を表示する(spotID指定)
void InterstitialMenuScene::showInterstitialWithSpotIdButtonCallback(cocos2d::Ref* pSender)
{
    NendInterstitialModule::showNADInterstitialView(interstitialSpotID);
}
// インタースティシャル広告を非表示にする
void InterstitialMenuScene::hideInterstitialWithSpotIdButtonCallback(cocos2d::Ref* pSender)
{
    // dismissボタンをタップしてから5秒後に広告を非表示する例
    this->runAction(Sequence::create(DelayTime::create(5.0f), CallFunc::create([=](){
        NendInterstitialModule::dismissNADInterstitialView();
    }), nullptr));
}

#pragma mark - 画面遷移
void InterstitialMenuScene::showPreviousSceneButtonCallback(Ref* pSender)
{
    Director::getInstance()->replaceScene(TransitionSlideInL::create(0.5f,HelloWorld::createScene()));
}

#pragma mark - EventDispatcher登録
// EventDispatcherで通知を受け取る
void InterstitialMenuScene::addEventDispatcher()
{
    // インタースティシャル（ロード結果）
    Director::getInstance()->getEventDispatcher()->addCustomEventListener(NADInterstitialDelegateLoadResultNotification,[&](cocos2d::EventCustom *event) {
        int *intValue = (int *)event->getUserData();
        int resultCode = *intValue;
        switch (resultCode) {
            case FINISH_LOAD_AD_INTERSTITIAL:
                // ロード完了
                log("FINISH_LOAD_AD_INTERSTITIAL");
                break;
            case FAIL_AD_DOWNLOAD_INTERSTITIAL:
                // ロード失敗
                log("FAIL_AD_DOWNLOAD_INTERSTITIAL");
                break;
            case INVALID_RESPONSE_TYPE_INTERSTITIAL:
                // 不正な広告タイプ
                log("INVALID_RESPONSE_TYPE_INTERSTITIAL");
                break;
            case FAIL_AD_REQUEST_INTERSTITIAL:
                // 抽選リクエスト失敗
                log("FAIL_AD_REQUEST_INTERSTITIAL");
                break;
            case FAIL_AD_INCOMPLETE_INTERSTITIAL:  //※Android のみ
                // 広告取得未完了
                log("FAIL_AD_INCOMPLETE_INTERSTITIAL");
                break;
            default:
                break;
        }
        
    });
    
    // インタースティシャル（ロード結果 & spotID）
    Director::getInstance()->getEventDispatcher()->addCustomEventListener(NADInterstitialDelegateLoadResultWithSpotIdNotification,[&](cocos2d::EventCustom *event) {
        
        int *resultArray = (int *)event->getUserData();
        int resultCode = resultArray[0];
        int spotId = resultArray[1];
        switch (resultCode) {
            case FINISH_LOAD_AD_INTERSTITIAL:
                // ロード完了
                log("FINISH_LOAD_AD_INTERSTITIAL:%d",spotId);
                break;
            case FAIL_AD_DOWNLOAD_INTERSTITIAL:
                // ロード失敗
                log("FAIL_AD_DOWNLOAD_INTERSTITIAL:%d",spotId);
                break;
            case INVALID_RESPONSE_TYPE_INTERSTITIAL:
                 // 不正な広告タイプ
                log("INVALID_RESPONSE_TYPE_INTERSTITIAL:%d",spotId);
                break;
            case FAIL_AD_REQUEST_INTERSTITIAL:
                // 抽選リクエスト失敗
                log("FAIL_AD_REQUEST_INTERSTITIAL:%d",spotId);
                break;
            case FAIL_AD_INCOMPLETE_INTERSTITIAL:  //※Android のみ
                // 広告取得未完了
                log("FAIL_AD_INCOMPLETE_INTERSTITIAL:%d",spotId);
                break;
            default:
                break;
        }
        
    });
    
    // インタースティシャル（表示結果）
    Director::getInstance()->getEventDispatcher()->addCustomEventListener(NADInterstitialDelegateShowResultNotification,[&](cocos2d::EventCustom *event) {
        int *intValue = (int *)event->getUserData();
        int resultCode = *intValue;
        switch (resultCode) {
            case SHOW_SUCCESS:
                // 表示成功
                log("SHOW_SUCCESS");
                break;
            case SHOW_ALREADY:
                // 既に表示済み
                log("SHOW_ALREADY");
                break;
            case SHOW_FREQUENCY_NOT_REACHABLE:
                // 広告のフリークエンシーカウントに未到達
                log("SHOW_FREQUENCY_NOT_REACHABLE");
                break;
            case REQUEST_INCOMPLETE:
                // 抽選リクエストに失敗
                log("REQUEST_INCOMPLETE");
                break;
            case LOAD_INCOMPLETE:
                // 抽選リクエストが実行されていない、もしくは実行中
                log("LOAD_INCOMPLETE");
                break;
            case DOWNLOAD_INCOMPLETE:
                // 広告ダウンロードが未完了
                log("DOWNLOAD_INCOMPLETE");
                break;
            default:
                break;
        }
        
    });
    
    // インタースティシャル（表示結果 & spotID）
    Director::getInstance()->getEventDispatcher()->addCustomEventListener(NADInterstitialDelegateShowResultWithSpotIdNotification,[&](cocos2d::EventCustom *event) {
        int *resultArray = (int *)event->getUserData();
        int resultCode = resultArray[0];
        int spotId = resultArray[1];
        switch (resultCode) {
            case SHOW_SUCCESS:
                // 表示成功
                log("SHOW_SUCCESS:%d",spotId);
                break;
            case SHOW_ALREADY:
                // 既に表示済み
                log("SHOW_ALREADY:%d",spotId);
                break;
            case SHOW_FREQUENCY_NOT_REACHABLE:
                // 広告のフリークエンシーカウントに未到達
                log("SHOW_FREQUENCY_NOT_REACHABLE:%d",spotId);
                break;
            case REQUEST_INCOMPLETE:
                // 抽選リクエストに失敗
                log("REQUEST_INCOMPLETE:%d",spotId);
                break;
            case LOAD_INCOMPLETE:
                // 抽選リクエストが実行されていない、もしくは実行中
                log("LOAD_INCOMPLETE:%d",spotId);
                break;
            case DOWNLOAD_INCOMPLETE:
                // 広告ダウンロードが未完了
                log("DOWNLOAD_INCOMPLETE:%d",spotId);
                break;
            default:
                break;
        }
    });
    
    // インタースティシャル（クリックタイプ）
    Director::getInstance()->getEventDispatcher()->addCustomEventListener(NADInterstitialDelegateClickResultNotification,[&](cocos2d::EventCustom *event) {
        int *intValue = (int *)event->getUserData();
        int resultCode = *intValue;
        switch (resultCode) {
            case CLICK_DOWNLOAD:
                // ダウンロードボタンがクリック
                log("CLICK_DOWNLOAD");
                break;
            case CLICK_CLOSE:
                // ×ボタンあるいは広告範囲外の領域がクリック
                log("CLICK_CLOSE");
                break;
            case CLICK_INFORMATION_INTERSTITIAL:
                // インフォメーションボタンクリック
                log("CLICK_INFORMATION_INTERSTITIAL");
                break;
            default:
                break;
        }
        
    });
    
    // インタースティシャル（クリックタイプ & spotID）
    Director::getInstance()->getEventDispatcher()->addCustomEventListener(NADInterstitialDelegateClickResultWithSpotIdNotification,[&](cocos2d::EventCustom *event) {
        
        int *resultArray = (int *)event->getUserData();
        int resultCode = resultArray[0];
        int spotId = resultArray[1];
        switch (resultCode) {
            case CLICK_DOWNLOAD:
                // ダウンロードボタンがクリック
                log("CLICK_DOWNLOAD:%d",spotId);
                break;
            case CLICK_CLOSE:
                // ×ボタンあるいは広告範囲外の領域がクリック
                log("CLICK_CLOSE:%d",spotId);
                break;
            case CLICK_INFORMATION_INTERSTITIAL:
                // インフォメーションボタンクリック
                log("CLICK_INFORMATION_INTERSTITIAL:%d",spotId);
                break;
            default:
                break;
        }
        
        
    });
    
}

#pragma mark - EventDispatcher登録の解除
// EventDispatcherの通知を停止
void InterstitialMenuScene::removeEventDispatcher()
{
    Director::getInstance()->getEventDispatcher()->removeCustomEventListeners(NADInterstitialDelegateLoadResultNotification);
    Director::getInstance()->getEventDispatcher()->removeCustomEventListeners(NADInterstitialDelegateLoadResultWithSpotIdNotification);
    Director::getInstance()->getEventDispatcher()->removeCustomEventListeners(NADInterstitialDelegateShowResultNotification);
    Director::getInstance()->getEventDispatcher()->removeCustomEventListeners(NADInterstitialDelegateShowResultWithSpotIdNotification);
    Director::getInstance()->getEventDispatcher()->removeCustomEventListeners(NADInterstitialDelegateClickResultNotification);
    Director::getInstance()->getEventDispatcher()->removeCustomEventListeners(NADInterstitialDelegateClickResultWithSpotIdNotification);
    
}

void InterstitialMenuScene::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event)
{
    
}

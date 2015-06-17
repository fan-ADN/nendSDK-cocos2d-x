//
//  IconMenuScene.cpp
//  HelloCpp
//
//  Created by F@N Communications, Inc.
//
//

#include "IconMenuScene.h"
#include "HelloWorldScene.h"
#include "NendIconModule.h"

USING_NS_CC;

static char apiKey[] = "0c734134519f25412ae9a9bff94783b81048ffbe";
static char spotID[] = "101282";

Scene* IconMenuScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = IconMenuScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool IconMenuScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();
    
    
    /////////////////////////////
    // 3. add your codes below...
    
    // add a label shows "Hello World"
    // create and initialize a label
    
    auto director = Director::getInstance();
    auto displayScale = director->getContentScaleFactor();

    auto font = String::create("fonts/arial.ttf");
    auto fontSize = 15 * displayScale;

    auto label = Label::createWithTTF("IconMenuScene", "fonts/Marker Felt.ttf", 24 * displayScale);
    
    // position the label on the center of the screen
    label->setPosition(Point(origin.x + visibleSize.width/2,
                             origin.y + visibleSize.height - label->getContentSize().height));
    
    // add the label as a child to this layer
    this->addChild(label, 1);

    auto createTopLabel = Label::createWithSystemFont("createTop", font->getCString(), fontSize);
    auto createTopItem = MenuItemLabel::create(createTopLabel, CC_CALLBACK_1(IconMenuScene::createIconTopCallback, this));
    auto createTopMenu = Menu::create(createTopItem, NULL);
    createTopMenu->setPosition(Point(visibleSize.width/2 + origin.x - 100 * displayScale, visibleSize.height/2 + origin.y + 150 * displayScale));
    this->addChild(createTopMenu);
    
    auto createBottomLabel = Label::createWithSystemFont("createBottom", font->getCString(), fontSize);
    auto createBottomItem = MenuItemLabel::create(createBottomLabel, CC_CALLBACK_1(IconMenuScene::createIconBottomCallback, this));
    auto createBottomMenu = Menu::create(createBottomItem, NULL);
    createBottomMenu->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y + 150 * displayScale));
    this->addChild(createBottomMenu);
    
    auto createUserLabel = Label::createWithSystemFont("createUser", font->getCString(), fontSize);
    auto createUserItem = MenuItemLabel::create(createUserLabel, CC_CALLBACK_1(IconMenuScene::createIconUserCallback, this));
    auto createUserMenu = Menu::create(createUserItem, NULL);
    createUserMenu->setPosition(Point(visibleSize.width/2 + origin.x + 100 * displayScale, visibleSize.height/2 + origin.y + 150 * displayScale));
    this->addChild(createUserMenu);
    
    auto createTopNumberLabel = Label::createWithSystemFont("createTopNumber", font->getCString(), fontSize);
    auto createTopNumberItem = MenuItemLabel::create(createTopNumberLabel, CC_CALLBACK_1(IconMenuScene::createIconWithNumberTopCallback, this));
    auto createTopNumberMenu = Menu::create(createTopNumberItem, NULL);
    createTopNumberMenu->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y + 100 * displayScale));
    this->addChild(createTopNumberMenu);
    
    auto createBottomNumberLabel = Label::createWithSystemFont("createBottomNumber", font->getCString(), fontSize);
    auto createBottomNumberItem = MenuItemLabel::create(createBottomNumberLabel, CC_CALLBACK_1(IconMenuScene::createIconWithNumberBottomCallback, this));
    auto createBottomNumberMenu = Menu::create(createBottomNumberItem, NULL);
    createBottomNumberMenu->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y + 50 * displayScale));
    this->addChild(createBottomNumberMenu);
    
    auto showLabel = Label::createWithSystemFont("show", font->getCString(), fontSize);
    auto showItem = MenuItemLabel::create(showLabel, CC_CALLBACK_1(IconMenuScene::showIconCallback, this));
    auto showMenu = Menu::create(showItem, NULL);
    showMenu->setPosition(Point(visibleSize.width/2 + origin.x - 100 * displayScale, visibleSize.height/2 + origin.y));
    this->addChild(showMenu);
    
    auto hideLabel = Label::createWithSystemFont("hide", font->getCString(), fontSize);
    auto hideItem = MenuItemLabel::create(hideLabel, CC_CALLBACK_1(IconMenuScene::hideIconCallback, this));
    auto hideMenu = Menu::create(hideItem, NULL);
    hideMenu->setPosition(Point(visibleSize.width/2 + origin.x + 100 * displayScale, visibleSize.height/2 + origin.y));
    this->addChild(hideMenu);
    
    auto pauseLabel = Label::createWithSystemFont("pause", font->getCString(), fontSize);
    auto pauseItem = MenuItemLabel::create(pauseLabel, CC_CALLBACK_1(IconMenuScene::pauseIconCallback, this));
    auto pauseMenu = Menu::create(pauseItem, NULL);
    pauseMenu->setPosition(Point(visibleSize.width/2 + origin.x - 100 * displayScale, visibleSize.height/2 + origin.y - 50 * displayScale));
    this->addChild(pauseMenu);
    
    auto releaseLabel = Label::createWithSystemFont("release", font->getCString(), fontSize);
    auto releaseItem = MenuItemLabel::create(releaseLabel, CC_CALLBACK_1(IconMenuScene::releaseIconCallback, this));
    auto releaseMenu = Menu::create(releaseItem, NULL);
    releaseMenu->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y - 50 * displayScale));
    this->addChild(releaseMenu);

    auto resumeLabel = Label::createWithSystemFont("resume", font->getCString(), fontSize);
    auto resumeItem = MenuItemLabel::create(resumeLabel, CC_CALLBACK_1(IconMenuScene::resumeIconCallback, this));
    auto resumeMenu = Menu::create(resumeItem, NULL);
    resumeMenu->setPosition(Point(visibleSize.width/2 + origin.x + 100 * displayScale, visibleSize.height/2 + origin.y - 50 * displayScale));
    this->addChild(resumeMenu);
    
    auto showPreviousLabel = Label::createWithSystemFont("Back", font->getCString(), fontSize);
    auto showPreviousItem = MenuItemLabel::create(showPreviousLabel, CC_CALLBACK_1(IconMenuScene::showPreviousSceneButtonCallback, this));
    auto showPreviousMenu = Menu::create(showPreviousItem, NULL);
    showPreviousMenu->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y - 150 * displayScale));
    this->addChild(showPreviousMenu);
    
    // EventDispatcher登録
    this->addEventDispatcher();
    
    return true;
}

void IconMenuScene::onEnter()
{
    CCLayer::onEnter();
}

void IconMenuScene::onExit()
{
    CCLayer::onExit();

    // アイコン広告のロードを一時停止する
    NendIconModule::pause();
    // アイコン広告を非表示にする
    NendIconModule::hideNADIconView();
    // アイコン広告のリソースを解放する
    NendIconModule::release();
    // EventDispatcher登録の解除
    this->removeEventDispatcher();
}

void IconMenuScene::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();
}

#pragma mark - メニューボタンのコールバック
// 画面上部中央に並べてアイコン広告を表示する
void IconMenuScene::createIconTopCallback(cocos2d::Ref* pSender)
{
    NendIconModule::createNADIconLoader(apiKey, spotID);
    NendIconModule::createNADIconViewTop();
    NendIconModule::load();
}
// 画面下部中央に並べてアイコン広告を生成する
void IconMenuScene::createIconBottomCallback(cocos2d::Ref* pSender)
{
    NendIconModule::createNADIconLoader(apiKey, spotID);
    NendIconModule::createNADIconViewBottom();
    NendIconModule::load();
}
// 位置を指定してアイコン広告を生成する
void IconMenuScene::createIconUserCallback(cocos2d::Ref* pSender)
{
    NendIconModule::createNADIconLoader(apiKey, spotID);
    NendIconModule::createNADIconView(Point(100,0));
    NendIconModule::load();
}
// 画面上部中央に並べてアイコン広告を表示する(表示数指定)
void IconMenuScene::createIconWithNumberTopCallback(cocos2d::Ref* pSender)
{
    NendIconModule::createNADIconLoader(apiKey, spotID);
    NendIconModule::createNADIconViewTop(5);
    NendIconModule::load();
}
// 画面下部中央に並べてアイコン広告を生成する(表示数指定)
void IconMenuScene::createIconWithNumberBottomCallback(cocos2d::Ref* pSender)
{
    NendIconModule::createNADIconLoader(apiKey, spotID);
    NendIconModule::createNADIconViewBottom(5);
    NendIconModule::load();
}
// アイコン広告を再表示する
void IconMenuScene::showIconCallback(cocos2d::Ref* pSender)
{
    NendIconModule::showNADIconView();
}
// アイコン広告を非表示にする
void IconMenuScene::hideIconCallback(cocos2d::Ref* pSender)
{
    NendIconModule::hideNADIconView();
}
// アイコン広告のロードを一時停止する
void IconMenuScene::pauseIconCallback(cocos2d::Ref* pSender)
{
    NendIconModule::pause();
}
// アイコン広告のロードを再開する
void IconMenuScene::resumeIconCallback(cocos2d::Ref* pSender)
{
    NendIconModule::resume();
}
// アイコン広告のリソースを解放する
void IconMenuScene::releaseIconCallback(cocos2d::Ref* pSender)
{
    NendIconModule::release();
}
// 前の画面に遷移する
void IconMenuScene::showPreviousSceneButtonCallback(cocos2d::Ref* pSender)
{
    Director::getInstance()->replaceScene(TransitionSlideInL::create(0.5f,HelloWorld::createScene()));
}

#pragma mark - EventDispatcher登録
void IconMenuScene::addEventDispatcher()
{
    // EventDispatcherで通知を受け取る
    // アイコン
    Director::getInstance()->getEventDispatcher()->addCustomEventListener(NADIconLoaderDelegateNotification,[&](cocos2d::EventCustom *event) {
        int *intValue = (int *)event->getUserData();
        int resultCode = *intValue;
        switch (resultCode) {
            case RECEIVE_AD_ICON:
            	// 広告受信成功
                log("RECEIVE_AD_ICON");
                break;
            case FAIL_TO_RECEIVE_AD_ICON:
            	// 広告受信失敗
                log("FAIL_TO_RECEIVE_AD_ICON");
                break;
            case CLICK_AD_ICON:
            	// アイコン広告クリック
                log("CLICK_AD_ICON");
                break;
            default:
                break;
        }
    });
}

#pragma mark - EventDispatcher登録の解除
void IconMenuScene::removeEventDispatcher()
{
    // EventDispatcherの通知を停止
    // アイコン
    Director::getInstance()->getEventDispatcher()->removeCustomEventListeners(NADIconLoaderDelegateNotification);
}

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
#include "IconMenuWithSpotIDScene.h"

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
    
    if (!LayerColor::initWithColor(Color4B(255, 255, 255, 255))) //RGBA
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

    std::string font = StringUtils::format("fonts/arial.ttf");
    auto fontSize = 15 * displayScale;

    auto label = Label::createWithTTF("IconMenuScene", "fonts/Marker Felt.ttf", 24 * displayScale);
    
    // position the label on the center of the screen
    label->setPosition(Point(origin.x + visibleSize.width/2,
                             origin.y + visibleSize.height - label->getContentSize().height));
    label->setColor(Color3B::BLACK);
    // add the label as a child to this layer
    this->addChild(label, 1);

    auto createTopLabel = Label::createWithSystemFont("createTop", font, fontSize);
    createTopLabel->setColor(Color3B::BLACK);
    auto createTopItem = MenuItemLabel::create(createTopLabel, CC_CALLBACK_1(IconMenuScene::createIconTopCallback, this));
    auto createTopMenu = Menu::create(createTopItem, NULL);
    createTopMenu->setPosition(Point(visibleSize.width/2 + origin.x - 100 * displayScale, visibleSize.height/2 + origin.y + 150 * displayScale));
    this->addChild(createTopMenu);
    
    auto createBottomLabel = Label::createWithSystemFont("createBottom", font, fontSize);
    createBottomLabel->setColor(Color3B::BLACK);
    auto createBottomItem = MenuItemLabel::create(createBottomLabel, CC_CALLBACK_1(IconMenuScene::createIconBottomCallback, this));
    auto createBottomMenu = Menu::create(createBottomItem, NULL);
    createBottomMenu->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y + 150 * displayScale));
    this->addChild(createBottomMenu);
    
    auto createUserLabel = Label::createWithSystemFont("createUser", font, fontSize);
    createUserLabel->setColor(Color3B::BLACK);
    auto createUserItem = MenuItemLabel::create(createUserLabel, CC_CALLBACK_1(IconMenuScene::createIconUserCallback, this));
    auto createUserMenu = Menu::create(createUserItem, NULL);
    createUserMenu->setPosition(Point(visibleSize.width/2 + origin.x + 100 * displayScale, visibleSize.height/2 + origin.y + 150 * displayScale));
    this->addChild(createUserMenu);
    
    auto createTopNumberLabel = Label::createWithSystemFont("createTopNum", font, fontSize);
    createTopNumberLabel->setColor(Color3B::BLACK);
    auto createTopNumberItem = MenuItemLabel::create(createTopNumberLabel, CC_CALLBACK_1(IconMenuScene::createIconWithNumberTopCallback, this));
    auto createTopNumberMenu = Menu::create(createTopNumberItem, NULL);
    createTopNumberMenu->setPosition(Point(visibleSize.width/2 + origin.x - 100 * displayScale, visibleSize.height/2 + origin.y + 100 * displayScale));
    this->addChild(createTopNumberMenu);
    
    auto createBottomNumberLabel = Label::createWithSystemFont("createBottomNum", font, fontSize);
    createBottomNumberLabel->setColor(Color3B::BLACK);
    auto createBottomNumberItem = MenuItemLabel::create(createBottomNumberLabel, CC_CALLBACK_1(IconMenuScene::createIconWithNumberBottomCallback, this));
    auto createBottomNumberMenu = Menu::create(createBottomNumberItem, NULL);
    createBottomNumberMenu->setPosition(Point(visibleSize.width/2 + origin.x + 100 * displayScale, visibleSize.height/2 + origin.y + 100 * displayScale));
    this->addChild(createBottomNumberMenu);
    
    auto titleSpaceLabel = Label::createWithSystemFont("titleSpaceOFF", font, fontSize);
    titleSpaceLabel->setColor(Color3B::BLACK);
    auto titleSpaceLabelItem = MenuItemLabel::create(titleSpaceLabel, CC_CALLBACK_1(IconMenuScene::spaceAndTitleDisableCallback, this));
    auto titleSpaceLabelItemMenu = Menu::create(titleSpaceLabelItem, NULL);
    titleSpaceLabelItemMenu->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y + 50 * displayScale));
    this->addChild(titleSpaceLabelItemMenu);

    auto spaceOffLabel = Label::createWithSystemFont("spaceOFF", font, fontSize);
    spaceOffLabel->setColor(Color3B::BLACK);
    auto spaceOffItem = MenuItemLabel::create(spaceOffLabel, CC_CALLBACK_1(IconMenuScene::spaceDisableCallback, this));
    auto spaceOffItemMenu = Menu::create(spaceOffItem, NULL);
    spaceOffItemMenu->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    this->addChild(spaceOffItemMenu);

    auto titleOffLabel = Label::createWithSystemFont("titleOFF", font, fontSize);
    titleOffLabel->setColor(Color3B::BLACK);
    auto titleOffItem = MenuItemLabel::create(titleOffLabel, CC_CALLBACK_1(IconMenuScene::titleDsableCallback, this));
    auto titleOffItemMenu = Menu::create(titleOffItem, NULL);
    titleOffItemMenu->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y - 50 * displayScale));
    this->addChild(titleOffItemMenu);

    auto showLabel = Label::createWithSystemFont("show", font, fontSize);
    showLabel->setColor(Color3B::BLACK);
    auto showItem = MenuItemLabel::create(showLabel, CC_CALLBACK_1(IconMenuScene::showIconCallback, this));
    auto showMenu = Menu::create(showItem, NULL);
    showMenu->setPosition(Point(visibleSize.width/2 + origin.x - 100 * displayScale, visibleSize.height/2 + origin.y + 50 * displayScale));
    this->addChild(showMenu);
    
    auto hideLabel = Label::createWithSystemFont("hide", font, fontSize);
    hideLabel->setColor(Color3B::BLACK);
    auto hideItem = MenuItemLabel::create(hideLabel, CC_CALLBACK_1(IconMenuScene::hideIconCallback, this));
    auto hideMenu = Menu::create(hideItem, NULL);
    hideMenu->setPosition(Point(visibleSize.width/2 + origin.x + 100 * displayScale, visibleSize.height/2 + origin.y + 50 * displayScale));
    this->addChild(hideMenu);

    auto pauseLabel = Label::createWithSystemFont("pause", font, fontSize);
    pauseLabel->setColor(Color3B::BLACK);
    auto pauseItem = MenuItemLabel::create(pauseLabel, CC_CALLBACK_1(IconMenuScene::pauseIconCallback, this));
    auto pauseMenu = Menu::create(pauseItem, NULL);
    pauseMenu->setPosition(Point(visibleSize.width/2 + origin.x - 100 * displayScale, visibleSize.height/2 + origin.y));
    this->addChild(pauseMenu);

    auto resumeLabel = Label::createWithSystemFont("resume", font, fontSize);
    resumeLabel->setColor(Color3B::BLACK);
    auto resumeItem = MenuItemLabel::create(resumeLabel, CC_CALLBACK_1(IconMenuScene::resumeIconCallback, this));
    auto resumeMenu = Menu::create(resumeItem, NULL);
    resumeMenu->setPosition(Point(visibleSize.width/2 + origin.x + 100 * displayScale, visibleSize.height/2 + origin.y));
    this->addChild(resumeMenu);

    auto releaseLabel = Label::createWithSystemFont("release", font, fontSize);
    releaseLabel->setColor(Color3B::BLACK);
    auto releaseItem = MenuItemLabel::create(releaseLabel, CC_CALLBACK_1(IconMenuScene::releaseIconCallback, this));
    auto releaseMenu = Menu::create(releaseItem, NULL);
    releaseMenu->setPosition(Point(visibleSize.width/2 + origin.x - 100 * displayScale, visibleSize.height/2 + origin.y - 50 * displayScale));
    this->addChild(releaseMenu);

    auto toNextSceneLabel = Label::createWithSystemFont("ToWithSpotIDMenu >", font, fontSize);
    toNextSceneLabel->setColor(Color3B::BLACK);
    auto toNextSceneItem = MenuItemLabel::create(toNextSceneLabel, CC_CALLBACK_1(IconMenuScene::toWithSpotIDMenuCallback, this));
    auto toNextSceneMenu = Menu::create(toNextSceneItem, NULL);
    toNextSceneMenu->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y - 100 * displayScale));
    this->addChild(toNextSceneMenu);

    auto showPreviousLabel = Label::createWithSystemFont("Back", font, fontSize);
    showPreviousLabel->setColor(Color3B::BLACK);
    auto showPreviousItem = MenuItemLabel::create(showPreviousLabel, CC_CALLBACK_1(IconMenuScene::showPreviousSceneButtonCallback, this));
    auto showPreviousMenu = Menu::create(showPreviousItem, NULL);
    showPreviousMenu->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y - 150 * displayScale));
    this->addChild(showPreviousMenu);

    return true;
}

void IconMenuScene::onEnter()
{
    Layer::onEnter();

    // EventDispatcher登録
    this->addEventDispatcher();
}

void IconMenuScene::onExit()
{
    Layer::onExit();
}

void IconMenuScene::onExitTransitionDidStart()
{
    // EventDispatcher登録の解除
    this->removeEventDispatcher();

    // アイコン広告のリソースを解放する
    NendIconModule::release();
}

void IconMenuScene::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();
}

#pragma mark - メニューボタンのコールバック
// 画面上部中央に並べてアイコン広告を表示する
void IconMenuScene::createIconTopCallback(cocos2d::Ref* pSender)
{
	this->releaseIconCallback(NULL);

    NendIconModule::createNADIconLoader(apiKey, spotID);
    NendIconModule::createNADIconViewTop();
    NendIconModule::load();
}
// 画面下部中央に並べてアイコン広告を生成する
void IconMenuScene::createIconBottomCallback(cocos2d::Ref* pSender)
{
	this->releaseIconCallback(NULL);

    NendIconModule::createNADIconLoader(apiKey, spotID);
    NendIconModule::createNADIconViewBottom();
    NendIconModule::load();
}
// 位置を指定してアイコン広告を生成する
void IconMenuScene::createIconUserCallback(cocos2d::Ref* pSender)
{
	this->releaseIconCallback(NULL);

    NendIconModule::createNADIconLoader(apiKey, spotID);
    for (int i = 0; i < 3; i++) {
        NendIconModule::createNADIconView(Point(100, 250 + 250 * i));
    }
    NendIconModule::load();
}
// 画面上部中央に並べてアイコン広告を表示する(表示数指定)
void IconMenuScene::createIconWithNumberTopCallback(cocos2d::Ref* pSender)
{
	this->releaseIconCallback(NULL);

    NendIconModule::createNADIconLoader(apiKey, spotID);
    NendIconModule::createNADIconViewTop(5);
    NendIconModule::load();
}
// 画面下部中央に並べてアイコン広告を生成する(表示数指定)
void IconMenuScene::createIconWithNumberBottomCallback(cocos2d::Ref* pSender)
{
	this->releaseIconCallback(NULL);

    NendIconModule::createNADIconLoader(apiKey, spotID);
    NendIconModule::createNADIconViewBottom(5);
    NendIconModule::load();
}
// タイトルと余白なしで画面下部中央に並べてアイコン広告を生成する
void IconMenuScene::spaceAndTitleDisableCallback(cocos2d::Ref* pSender)
{
	this->releaseIconCallback(NULL);

    NendIconModule::createNADIconLoader(apiKey, spotID);
    NendIconModule::createNADIconViewBottom(spotID, false, false, Color3B(0, 100, 255));
    NendIconModule::load();
}
// 余白なしで画面上部中央に並べてアイコン広告を生成する
void IconMenuScene::spaceDisableCallback(cocos2d::Ref* pSender)
{
	this->releaseIconCallback(NULL);

    NendIconModule::createNADIconLoader(apiKey, spotID);
    NendIconModule::createNADIconViewBottom(spotID, true, false, Color3B(0, 255, 255));
    NendIconModule::load();
}
// タイトルなしで画面下部中央に並べてアイコン広告を生成する
void IconMenuScene::titleDsableCallback(cocos2d::Ref* pSender)
{
	this->releaseIconCallback(NULL);

    NendIconModule::createNADIconLoader(apiKey, spotID);
    NendIconModule::createNADIconViewBottom(spotID, false, true, Color3B(0, 0, 0));
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
// 次の画面に遷移する
void IconMenuScene::toWithSpotIDMenuCallback(cocos2d::Ref* pSender)
{
    Director::getInstance()->replaceScene(TransitionSlideInR::create(0.5f,IconMenuWithSpotIDScene::createScene()));
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
    Director::getInstance()->getEventDispatcher()->removeCustomEventListeners(NADIconLoaderDelegateNotification);
}

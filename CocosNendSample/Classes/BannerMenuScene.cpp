//
//  BannerMenuScene.cpp
//  CocosNendSample
//
//  Created by F@N Communications, Inc.
//
//

#include <stdio.h>
#include "BannerMenuScene.h"
#include "HelloWorldScene.h"
#include "BannerViewScene.h"

USING_NS_CC;

Scene* BannerMenuScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = BannerMenuScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool BannerMenuScene::init()
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
    
    std::string font = StringUtils::format("fonts/arial.ttf");
    auto fontSize = 15;
    
    auto label = Label::createWithTTF("BannerMenuScene", "fonts/Marker Felt.ttf", 24);
    
    // position the label on the center of the screen
    label->setPosition(Point(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));
    
    // add the label as a child to this layer
    this->addChild(label, 1);
    
    auto bannerLabel_320_50 = Label::createWithSystemFont("320x50", font, fontSize);
    auto bannerItem_320_50 = MenuItemLabel::create(bannerLabel_320_50, CC_CALLBACK_1(BannerMenuScene::showBanner320_50ViewSceneButtonCallback, this));
    auto bannerMenu_320_50 = Menu::create(bannerItem_320_50, NULL);
    bannerMenu_320_50->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y + 150));
    this->addChild(bannerMenu_320_50);
    
    auto bannerLabel_320_100 = Label::createWithSystemFont("320x100", font, fontSize);
    auto bannerItem_320_100 = MenuItemLabel::create(bannerLabel_320_100, CC_CALLBACK_1(BannerMenuScene::showBanner320_100ViewSceneButtonCallback, this));
    auto bannerMenu_320_100 = Menu::create(bannerItem_320_100, NULL);
    bannerMenu_320_100->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y + 100));
    this->addChild(bannerMenu_320_100);
    
    auto bannerLabel_300_100 = Label::createWithSystemFont("300x100", font, fontSize);
    auto bannerItem_300_100 = MenuItemLabel::create(bannerLabel_300_100, CC_CALLBACK_1(BannerMenuScene::showBanner300_100ViewSceneButtonCallback, this));
    auto bannerMenu_300_100 = Menu::create(bannerItem_300_100, NULL);
    bannerMenu_300_100->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y + 50));
    this->addChild(bannerMenu_300_100);
    
    auto bannerLabel_300_250 = Label::createWithSystemFont("300x250", font, fontSize);
    auto bannerItem_300_250 = MenuItemLabel::create(bannerLabel_300_250, CC_CALLBACK_1(BannerMenuScene::showBanner300_250ViewSceneButtonCallback, this));
    auto bannerMenu_300_250 = Menu::create(bannerItem_300_250, NULL);
    bannerMenu_300_250->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    this->addChild(bannerMenu_300_250);
    
    auto bannerLabel_728_90 = Label::createWithSystemFont("728_90", font, fontSize);
    auto bannerItem_728_90 = MenuItemLabel::create(bannerLabel_728_90, CC_CALLBACK_1(BannerMenuScene::showBanner728_90ViewSceneButtonCallback, this));
    auto bannerMenu_728_90 = Menu::create(bannerItem_728_90, NULL);
    bannerMenu_728_90->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y - 50));
    this->addChild(bannerMenu_728_90);

    auto showPreviousLabel = Label::createWithSystemFont("Back", font, fontSize);
    auto showPreviousItem = MenuItemLabel::create(showPreviousLabel, CC_CALLBACK_1(BannerMenuScene::showPreviousSceneButtonCallback, this));
    auto showPreviousMenu = Menu::create(showPreviousItem, NULL);
    showPreviousMenu->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y - 150));
    this->addChild(showPreviousMenu);
    
    return true;
}

void BannerMenuScene::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

#endif
}


#pragma mark - メニューボタンのコールバック
void BannerMenuScene::showBanner320_50ViewSceneButtonCallback(Ref* pSender)
{
    Director::getInstance()->replaceScene(TransitionSlideInR::create(0.5f,BannerViewScene::createScene(BANNER_320_50)));
}
void BannerMenuScene::showBanner320_100ViewSceneButtonCallback(Ref* pSender)
{
    Director::getInstance()->replaceScene(TransitionSlideInR::create(0.5f,BannerViewScene::createScene(BANNER_320_100)));
}
void BannerMenuScene::showBanner300_100ViewSceneButtonCallback(Ref* pSender)
{
    Director::getInstance()->replaceScene(TransitionSlideInR::create(0.5f,BannerViewScene::createScene(BANNER_300_100)));
}
void BannerMenuScene::showBanner300_250ViewSceneButtonCallback(Ref* pSender)
{
    Director::getInstance()->replaceScene(TransitionSlideInR::create(0.5f,BannerViewScene::createScene(BANNER_300_250)));
}
void BannerMenuScene::showBanner728_90ViewSceneButtonCallback(Ref* pSender)
{
    Director::getInstance()->replaceScene(TransitionSlideInR::create(0.5f,BannerViewScene::createScene(BANNER_728_90)));
}
void BannerMenuScene::showPreviousSceneButtonCallback(Ref* pSender)
{
    Director::getInstance()->replaceScene(TransitionSlideInL::create(0.5f,HelloWorld::createScene()));
}

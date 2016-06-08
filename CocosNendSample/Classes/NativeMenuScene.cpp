//
//  NativeMenuScene.cpp
//  CocosNendSample
//
//  Created by F@N Communications, Inc.
//
//

#include "NativeMenuScene.h"
#include "HelloWorldScene.h"
#include "NativeInfeedViewScene.h"
#include "NativeTelopViewScene.h"

USING_NS_CC;

Scene* NativeMenuScene::createScene()
{
    Scene* scene = Scene::create();
    NativeMenuScene* layer = NativeMenuScene::create();
    scene->addChild(layer);
    return scene;
}

bool NativeMenuScene::init()
{
    if (!Layer::init()) {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();

    auto font = "fonts/arial.ttf";
    auto fontSize = 15;

    auto label = Label::createWithTTF("NativeAdMenuScene", "fonts/Marker Felt.ttf", 24);
    
    // position the label on the center of the screen
    label->setPosition(Point(origin.x + visibleSize.width/2,
                             origin.y + visibleSize.height - label->getContentSize().height));
    
    // add the label as a child to this layer
    this->addChild(label, 1);

    auto showSmallSquareLabel = Label::createWithSystemFont("Show Small-Square", font, fontSize);
    auto showSmallSquareItem = MenuItemLabel::create(showSmallSquareLabel, CC_CALLBACK_1(NativeMenuScene::showNativeViewSceneButtonCallback, this, NATIVE_SMALL_SQUARE));
    auto showSmallSquareMenu = Menu::create(showSmallSquareItem, NULL);
    this->addChild(showSmallSquareMenu);

    showSmallSquareMenu->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y + 100));

    auto showSmallWideLabel = Label::createWithSystemFont("Show Small-Wide", font, fontSize);
    auto showSmallWideItem = MenuItemLabel::create(showSmallWideLabel, CC_CALLBACK_1(NativeMenuScene::showNativeViewSceneButtonCallback, this, NATIVE_SMALL_WIDE));
    auto showSmallWideMenu = Menu::create(showSmallWideItem, NULL);
    this->addChild(showSmallWideMenu);
    
    showSmallWideMenu->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y + 50));

    auto showLargeWideLabel = Label::createWithSystemFont("Show Large-Wide", font, fontSize);
    auto showLargeWideItem = MenuItemLabel::create(showLargeWideLabel, CC_CALLBACK_1(NativeMenuScene::showNativeViewSceneButtonCallback, this, NATIVE_LARGE_WIDE));
    auto showLargeWideMenu = Menu::create(showLargeWideItem, NULL);
    this->addChild(showLargeWideMenu);
    
    showLargeWideMenu->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y - 0));

    auto showTextOnlyLabel = Label::createWithSystemFont("Show Text Only", font, fontSize);
    auto showTextOnlyItem = MenuItemLabel::create(showTextOnlyLabel, CC_CALLBACK_1(NativeMenuScene::showNativeViewSceneButtonCallback, this, NATIVE_TEXT_ONLY));
    auto showTextOnlyMenu = Menu::create(showTextOnlyItem, NULL);
    this->addChild(showTextOnlyMenu);
    
    showTextOnlyMenu->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y - 50));

    auto showInfeedLabel = Label::createWithSystemFont("Show Infeed", font, fontSize);
    auto showInfeedItem = MenuItemLabel::create(showInfeedLabel, CC_CALLBACK_1(NativeMenuScene::showNativeInfeedViewSceneButtonCallback, this));
    auto showInfeedMenu = Menu::create(showInfeedItem, NULL);
    this->addChild(showInfeedMenu);
    
    showInfeedMenu->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y - 100));

    auto showTelopLabel = Label::createWithSystemFont("Show Telop", font, fontSize);
    auto showTelopItem = MenuItemLabel::create(showTelopLabel, CC_CALLBACK_1(NativeMenuScene::showNativeTelopViewSceneButtonCallback, this));
    auto showTelopMenu = Menu::create(showTelopItem, NULL);
    this->addChild(showTelopMenu);
    
    showTelopMenu->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y - 150));

    auto showPreviousLabel = Label::createWithSystemFont("Back", font, fontSize);
    auto showPreviousItem = MenuItemLabel::create(showPreviousLabel, CC_CALLBACK_1(NativeMenuScene::showPreviousSceneButtonCallback, this));
    auto showPreviousMenu = Menu::create(showPreviousItem, NULL);
    showPreviousMenu->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y - 200));
    this->addChild(showPreviousMenu);

    return true;
}

void NativeMenuScene::showNativeViewSceneButtonCallback(Ref* pSender, NativeType type)
{
    Director::getInstance()->replaceScene(TransitionSlideInR::create(0.5f,NativeViewScene::createScene(type)));
}

void NativeMenuScene::showNativeInfeedViewSceneButtonCallback(Ref* pSender)
{
    Director::getInstance()->replaceScene(TransitionSlideInR::create(0.5f,NativeInfeedViewScene::createScene()));
}

void NativeMenuScene::showNativeTelopViewSceneButtonCallback(Ref* pSender)
{
    Director::getInstance()->replaceScene(TransitionSlideInR::create(0.5f, NativeTelopViewScene::createScene()));
}

void NativeMenuScene::showPreviousSceneButtonCallback(Ref* pSender)
{
    Director::getInstance()->replaceScene(TransitionSlideInL::create(0.5f,HelloWorld::createScene()));
}


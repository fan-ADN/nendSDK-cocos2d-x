#include "HelloWorldScene.h"
#include "BannerMenuScene.h"
#include "InterstitialMenuScene.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "IconMenuScene.h"
#endif

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
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
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Point(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Point::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    auto director = Director::getInstance();
    auto displayScale = director->getContentScaleFactor();
    
    auto font = String::create("fonts/arial.ttf");
    auto fontSize = 15 * displayScale;
    
    auto label = Label::createWithTTF("NendSDK Cocos2d-x Sample", "fonts/Marker Felt.ttf", 24 *displayScale);
    
    // position the label on the center of the screen
    label->setPosition(Point(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);

    auto showBannerLabel = Label::createWithSystemFont("Show BannerMenuScene", font->getCString(), fontSize);
    auto showBannerItem = MenuItemLabel::create(showBannerLabel, CC_CALLBACK_1(HelloWorld::showBannerSceneButtonCallback, this));
    auto showBannerMenu = Menu::create(showBannerItem, NULL);
    showBannerMenu->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y + 100 * displayScale));
    this->addChild(showBannerMenu);
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    auto showIconLabel = Label::createWithSystemFont("Show IconMenuScene", font->getCString(), fontSize);
    auto showIconItem = MenuItemLabel::create(showIconLabel, CC_CALLBACK_1(HelloWorld::showIconSceneButtonCallback, this));
    auto showIconMenu = Menu::create(showIconItem, NULL);
    showIconMenu->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    this->addChild(showIconMenu);
#endif
    
    auto showInterstitialLabel = Label::createWithSystemFont("Show InterstitialMenuScene", font->getCString(), fontSize);
    auto showInterstitialItem = MenuItemLabel::create(showInterstitialLabel, CC_CALLBACK_1(HelloWorld::showInterstitialSceneButtonCallback, this));
    auto showInterstitialMenu = Menu::create(showInterstitialItem, NULL);
    showInterstitialMenu->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y - 100 * displayScale));
    this->addChild(showInterstitialMenu);
    
    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

#endif
}


void HelloWorld::showBannerSceneButtonCallback(Ref* pSender)
{
    Director::getInstance()->replaceScene(TransitionSlideInR::create(0.5f,BannerMenuScene::createScene()));
}

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
void HelloWorld::showIconSceneButtonCallback(Ref* pSender)
{
    Director::getInstance()->replaceScene(TransitionSlideInR::create(0.5f,IconMenuScene::createScene()));
}
#endif

void HelloWorld::showInterstitialSceneButtonCallback(Ref* pSender)
{
    Director::getInstance()->replaceScene(TransitionSlideInR::create(0.5f,InterstitialMenuScene::createScene()));
}

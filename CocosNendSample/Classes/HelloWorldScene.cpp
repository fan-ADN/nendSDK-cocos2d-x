#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "BannerMenuScene.h"
#include "InterstitialMenuScene.h"
#include "BannerViewWithSpotIDScene.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "IconMenuScene.h"
#endif
#include "NativeMenuScene.h"
#include "FullBoardAdScene.h"

USING_NS_CC;

static const std::string font = StringUtils::format("fonts/arial.ttf");
static const float fontSize = 15.0f;

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
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
    closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...
    
    auto label = Label::createWithTTF("NendSDK Cocos2d-x Sample", "fonts/Marker Felt.ttf", 24);
    
    // position the label on the center of the screen
    label->setPosition(Point(origin.x + visibleSize.width/2,
                             origin.y + visibleSize.height - label->getContentSize().height));
    
    // add the label as a child to this layer
    this->addChild(label, 1);
    
    Vector<MenuItem *> vec;
    vec.pushBack(this->createMenuItem("Show BannerMenuScene", CC_CALLBACK_1(HelloWorld::showBannerSceneButtonCallback, this)));
    vec.pushBack(this->createMenuItem("Show BannerViewWithSpotIDScene", CC_CALLBACK_1(HelloWorld::showBannerWithSpotIDSceneButtonCallback, this)));
    vec.pushBack(this->createMenuItem("Show InterstitialMenuScene", CC_CALLBACK_1(HelloWorld::showInterstitialSceneButtonCallback, this)));
    vec.pushBack(this->createMenuItem("Show NativeAdMenuScene", CC_CALLBACK_1(HelloWorld::showNativeAdSceneButtonCallback, this)));
    vec.pushBack(this->createMenuItem("Show FullBoardAdScene", CC_CALLBACK_1(HelloWorld::showFullBoardAdSceneButtonCallback, this)));
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    vec.pushBack(this->createMenuItem("Show IconMenuScene", CC_CALLBACK_1(HelloWorld::showIconSceneButtonCallback, this)));
#endif
    
    auto menus = Menu::createWithArray(vec);
    menus->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    menus->alignItemsVerticallyWithPadding(24.0f);
    this->addChild(menus);

    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}


void HelloWorld::showBannerSceneButtonCallback(Ref* pSender)
{
    Director::getInstance()->replaceScene(TransitionSlideInR::create(0.5f,BannerMenuScene::createScene()));
}

void HelloWorld::showBannerWithSpotIDSceneButtonCallback(Ref* pSender)
{
    Director::getInstance()->replaceScene(TransitionSlideInR::create(0.5f,BannerViewWithSpotIDScene::createScene()));
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

void HelloWorld::showNativeAdSceneButtonCallback(Ref* pSender)
{
    Director::getInstance()->replaceScene(TransitionSlideInR::create(0.5f,NativeMenuScene::createScene()));
}

void HelloWorld::showFullBoardAdSceneButtonCallback(Ref* pSender)
{
    Director::getInstance()->replaceScene(TransitionSlideInR::create(0.5f, FullBoardAdScene::createScene()));
}

MenuItem* HelloWorld::createMenuItem(const std::string& title, const ccMenuCallback& callback)
{
    auto label = Label::createWithSystemFont(title, font, fontSize);
    auto item = MenuItemLabel::create(label, callback);
    return item;
}


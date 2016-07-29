//
//  NativeTelopViewScene.cpp
//  CocosNendSample
//

#include "NativeTelopViewScene.h"

#include "NativeMenuScene.h"

USING_NS_CC;

static const float speed = 50.0f;
static const float delay = 1.0f;

using namespace nend_module;

Scene* NativeTelopViewScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = NativeTelopViewScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

NativeTelopViewScene::~NativeTelopViewScene()
{
    if (_client) {
        delete _client;
        _client = nullptr;
    }
}

// on "init" you need to initialize your instance
bool NativeTelopViewScene::init()
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
                                           CC_CALLBACK_1(NativeTelopViewScene::menuCloseCallback, this));
    
    closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width / 2 ,
                                origin.y + closeItem->getContentSize().height / 2));
    
    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu);
    
    /////////////////////////////
    // 3. add your codes below...
    
    auto margin = 4.0f;
    
    auto adBackground = LayerColor::create(Color4B::YELLOW, 240, 64);
    adBackground->setPosition(Point((visibleSize.width - adBackground->getContentSize().width) / 2 + origin.x,
                                    (visibleSize.height - adBackground->getContentSize().height) / 2 + origin.y));
    this->addChild(adBackground);
    
    _adNode = LayerColor::create(Color4B::BLACK, adBackground->getContentSize().width - margin, adBackground->getContentSize().height - margin);
    _adNode->setPosition(Point(margin / 2, margin / 2));

    auto clippingNode = ClippingRectangleNode::create(Rect(_adNode->getPosition().x, _adNode->getPosition().y, _adNode->getContentSize().width, _adNode->getContentSize().height));
    clippingNode->addChild(_adNode);
    adBackground->addChild(clippingNode);

    _adImage = Sprite::create();
    _adImage->setName("AdImage");
    _adImage->setContentSize(Size(80, 60));
    _adImage->setPosition(Point(_adImage->getContentSize().width / 2, _adImage->getContentSize().height / 2));

    _prText = Label::create();
    _prText->setName("PR");
    _prText->setWidth(20);
    _prText->setAlignment(TextHAlignment::CENTER, TextVAlignment::CENTER);
    _prText->setDimensions(20, _adNode->getContentSize().height);
    _prText->setTextColor(Color4B::GREEN);
    _prText->setSystemFontSize(20.f);
    _prText->setPosition(Point(_adImage->getContentSize().width + _prText->getWidth() / 2, _adNode->getContentSize().height / 2));
    
    _shortText = Label::create();
    _shortText->setName("ShortText");
    _shortText->setWidth(_adNode->getContentSize().width - _adImage->getContentSize().width - _prText->getWidth());
    _shortText->setHeight(20);
    _shortText->setTextColor(Color4B::WHITE);
    _shortText->setSystemFontSize(20.f);
    _shortText->setPosition(Point(_adImage->getContentSize().width + _prText->getWidth() + _shortText->getWidth() / 2, _adNode->getContentSize().height / 2));
    _shortText->enableWrap(false);
    
    auto prBackground = LayerColor::create(Color4B::BLACK, _prText->getWidth(), _adNode->getContentSize().height);
    prBackground->setPosition(Point(_adImage->getContentSize().width, 0));
    
    _adNode->addChild(_shortText);
    _adNode->addChild(_adImage);
    _adNode->addChild(prBackground);
    _adNode->addChild(_prText);

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    const auto apiKey = "a3972604a76864dd110d0b02204f4b72adb092ae";
    const auto spotId = "485502";
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    const auto apiKey = "186927de979c5e542ee1ef111cc69c52e37a58f9";
    const auto spotId = "485517";
#endif
    
    _client = new NendNativeAdClient(apiKey, spotId);

    return true;
}

void NativeTelopViewScene::onEnter()
{
    Layer::onEnter();
    
    _client->loadAd([=](NendNativeAd *nativeAd, NendNativeLoadResultCode code, std::string errorMessage) {
        if (code == NEND_SUCCESS_LOAD_AD) {
            _prText->setString(nativeAd->prTextForAdvertisingExplicitly(NAD_NATIVE_ADVERTISING_EXPLIICITY_PR));
            _shortText->setString(nativeAd->getShortText());
            nativeAd->downloadAdImage([=](Texture2D* adImageTexture, std::string errorMessage){
                if (nullptr != adImageTexture) {
                    _adImage->setTexture(adImageTexture);
                    cocos2d::Rect rect = cocos2d::Rect();
                    rect.size = adImageTexture->getContentSize();
                    _adImage->setTextureRect(rect);
                    
                    _shortText->setDimensions(0, _shortText->getContentSize().height);
                    _shortText->Label::setPosition(Point(_adImage->getContentSize().width + _prText->getContentSize().width + _shortText->getContentSize().width / 2, _shortText->getPosition().y));
                    this->runAction(Sequence::create(DelayTime::create(delay), CallFunc::create([this]() {
                        this->scroll();
                    }), nullptr));
                }
            });
            nativeAd->activateAdView(_adNode, _prText);

        } else {
            CCLOG("NativeAd load error. code:%d, Message:%s", code, errorMessage.c_str());
        }
    });
}

void NativeTelopViewScene::onExit()
{
    Layer::onExit();
    _shortText->stopAllActions();
}

void NativeTelopViewScene::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->replaceScene(TransitionSlideInL::create(0.5f, NativeMenuScene::createScene()));
}

void NativeTelopViewScene::scroll()
{
    auto to = _shortText->getContentSize().width / 2 * -1;
    auto distance = _shortText->getPosition().x - to;
    auto callback = CallFuncN::create(CC_CALLBACK_1(NativeTelopViewScene::scrollFinished, this));
    auto move = MoveTo::create(distance / speed, Vec2(to, _shortText->getPosition().y));
    auto seq = Sequence::create(move, callback, NULL);
    _shortText->runAction(seq);
}

void NativeTelopViewScene::scrollFinished(cocos2d::Node *sender)
{
    _shortText->Label::setPosition(Point(_adNode->getContentSize().width + _shortText->getContentSize().width / 2, _shortText->getPosition().y));
    this->scroll();
}
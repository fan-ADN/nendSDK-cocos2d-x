//
//  NativeCustomViewScene.cpp
//  CocosNendSample
//
//  Created by FAN Communications, Inc.
//
//

#include "NativeCustomViewScene.h"
#include "NativeMenuScene.h"
#include "NendNativeAdLog.h"

USING_NS_CC;
using namespace nend_module;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
const auto apiKey = "30fda4b3386e793a14b27bedb4dcd29f03d638e5";
const auto spotId = "485504";
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
const auto apiKey = "a88c0bcaa2646c4ef8b2b656fd38d6785762f2ff";
const auto spotId = "485520";
#endif

// layout
const Size  layerSize = Size(320, 380);
const Point prLabelPoint = Point(10, 8);
const Size  prLabelSize = Size(40, 21);
const float prLabelFontSize = 14;
const Point shortTextLabelPoint = Point(10, 326);
const Size  shortTextLabelSize = Size(254, 40);
const float shortTextLabelFontSize = 14;
const Point longTextLabelPoint = Point(10, 95);
const Size  longTextLabelSize = Size(300, 35);
const float longTextLabelFontSize = 14;
const Point promotionNameLabelPoint = Point(10, 66);
const Size  promotionNameLabelSize = Size(300, 21);
const float promotionNameLabelFontSize = 14;
const Point promotionURLLabelPoint = Point(10, 37);
const Size  promotionURLLabelSize = Size(300, 21);
const float promotionURLLabelFontSize = 14;
const Point actionTextLabelPoint = Point(210, 8);
const Size  actionTextLabelSize = Size(100, 21);
const float actionTextLabelFontSize =14;
const Point adImageSpritePoint = Point(10, 138);
const Point logoImageSpritePoint = Point(272, 326);

const int autoReloadInterval = 30;
bool isAutoReload = false;
const auto startAutoReloadStr = "Start AutoReload";
const auto stopAutoReloadStr = "Stop AutoReload";

NativeCustomViewScene::NativeCustomViewScene(){
}

NativeCustomViewScene::~NativeCustomViewScene(){
    // Scene 解放時に NendNativeAdClient を解放します
    if (_nativeAdClient) {
        delete _nativeAdClient;
        _nativeAdClient = nullptr;
    }
}

Scene* NativeCustomViewScene::createScene()
{
    return NativeCustomViewScene::create();
}

bool NativeCustomViewScene::init()
{
    if (!Scene::init()) {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();
    
    auto label = Label::createWithTTF("NativeAdViewScene", "fonts/Marker Felt.ttf", 24);
    label->setPosition(Point(origin.x + visibleSize.width/2,
                             origin.y + visibleSize.height - label->getContentSize().height));
    this->addChild(label, 1);
    
    auto showPreviousLabel = Label::createWithSystemFont("Back", "fonts/arial.ttf", 15);
    auto showPreviousItem = MenuItemLabel::create(showPreviousLabel, CC_CALLBACK_1(NativeCustomViewScene::showPreviousSceneButtonCallback, this));
    auto showPreviousMenu = Menu::create(showPreviousItem, NULL);
    showPreviousMenu->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y - 210));
    this->addChild(showPreviousMenu);

    auto switchAutoReloadLabel = Label::createWithSystemFont(startAutoReloadStr, "fonts/arial.ttf", 15);
    auto switchAutoReloadItem = MenuItemLabel::create(switchAutoReloadLabel, CC_CALLBACK_1(NativeCustomViewScene::switchAutoReloadButtonCallback, this, switchAutoReloadLabel));
    auto switchAutoReloadMenu = Menu::create(switchAutoReloadItem, NULL);
    switchAutoReloadMenu->setPosition(Point(visibleSize.width/2 + origin.x + 95, visibleSize.height/2 + origin.y - 210));
    this->addChild(switchAutoReloadMenu);

    _adLayer = nullptr;
    _nativeAdClient = nullptr;

    // NendNativeAdClient クラスのインスタンスを生成します
    _nativeAdClient = new NendNativeAdClient(apiKey, spotId);
    
    this->makeAndLoadNativeAd();

    return true;
}

void NativeCustomViewScene::showPreviousSceneButtonCallback(Ref* pSender)
{
    Director::getInstance()->replaceScene(TransitionSlideInL::create(0.5f,NativeMenuScene::createScene()));
}

void NativeCustomViewScene::makeAndLoadNativeAd(){
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    _adLayer = this->makeNativeAdLayer();
    _adLayer->setPosition(Point((visibleSize.width - _adLayer->getContentSize().width) /2, (visibleSize.height - _adLayer->getContentSize().height) /2));
    this->addChild(_adLayer);
    
    this->loadNativeAd();
}

LayerColor * NativeCustomViewScene::makeNativeAdLayer()
{
    // ネイティブ広告を表示する領域を作成します
    auto adLayer = LayerColor::create(Color4B::WHITE, layerSize.width, layerSize.height);
    
    // 広告要素を作成し 上記で作成した領域に配置します
    
    // 広告明示
    _prLabel = Label::create();
    _prLabel->setTextColor(Color4B::BLACK);
    _prLabel->setAnchorPoint(Point(0,0));
    _prLabel->setPosition(prLabelPoint);
    _prLabel->setWidth(prLabelSize.width);
    _prLabel->setHeight(prLabelSize.height);
    _prLabel->setSystemFontSize(prLabelFontSize);
    adLayer->addChild(_prLabel);
    
    // 広告見出し
    _shortTextLabel = Label::create();
    _shortTextLabel->setTextColor(Color4B::BLACK);
    _shortTextLabel->setAnchorPoint(Point(0,0));
    _shortTextLabel->setPosition(shortTextLabelPoint);
    _shortTextLabel->setWidth(shortTextLabelSize.width);
    _shortTextLabel->setHeight(shortTextLabelSize.height);
    _shortTextLabel->setSystemFontSize(shortTextLabelFontSize);
    adLayer->addChild(_shortTextLabel);
    
    // 広告文
    _longTextLabel = Label::create();
    _longTextLabel->setTextColor(Color4B::BLACK);
    _longTextLabel->setAnchorPoint(Point(0,0));
    _longTextLabel->setPosition(longTextLabelPoint);
    _longTextLabel->setWidth(longTextLabelSize.width);
    _longTextLabel->setHeight(longTextLabelSize.height);
    _longTextLabel->setSystemFontSize(longTextLabelFontSize);
    adLayer->addChild(_longTextLabel);
    
    // プロモーション名
    _promotionNameLabel = Label::create();
    _promotionNameLabel->setTextColor(Color4B::BLACK);
    _promotionNameLabel->setAnchorPoint(Point(0,0));
    _promotionNameLabel->setPosition(promotionNameLabelPoint);
    _promotionNameLabel->setWidth(promotionNameLabelSize.width);
    _promotionNameLabel->setHeight(promotionNameLabelSize.height);
    _promotionNameLabel->setSystemFontSize(promotionNameLabelFontSize);
    adLayer->addChild(_promotionNameLabel);
    
    // プロモーションURL
    _promotionURLLabel = Label::create();
    _promotionURLLabel->setTextColor(Color4B::BLACK);
    _promotionURLLabel->setAnchorPoint(Point(0,0));
    _promotionURLLabel->setPosition(promotionURLLabelPoint);
    _promotionURLLabel->setWidth(promotionURLLabelSize.width);
    _promotionURLLabel->setHeight(promotionURLLabelSize.height);
    _promotionURLLabel->setSystemFontSize(promotionURLLabelFontSize);
    adLayer->addChild(_promotionURLLabel);
    
    // アクションボタン
    _actionTextLabel = Label::create();
    _actionTextLabel->setTextColor(Color4B::BLUE);
    _actionTextLabel->setAnchorPoint(Point(0,0));
    _actionTextLabel->setPosition(actionTextLabelPoint);
    _actionTextLabel->setWidth(actionTextLabelSize.width);
    _actionTextLabel->setHeight(actionTextLabelSize.height);
    _actionTextLabel->setSystemFontSize(actionTextLabelFontSize);
    _actionTextLabel->setTextColor(Color4B::BLUE);
    adLayer->addChild(_actionTextLabel);
    
    // 広告画像
    _adImageSprite = Sprite::create();
    _adImageSprite->setAnchorPoint(Point(0,0));

    // 広告画像(クリップ)
    auto clipNode = NendNativeClippingNode::create(Size(300.f, 180.f), 10.f, _adImageSprite, NEND_CLIP_CENTER);
    clipNode->setPosition(adImageSpritePoint);
    clipNode->addChild(_adImageSprite);
    adLayer->addChild(clipNode);
    
    // ロゴ画像
    _logoImageSprite = Sprite::create();
    _logoImageSprite->setAnchorPoint(Point(0,0));
    _logoImageSprite->setPosition(logoImageSpritePoint);
    adLayer->addChild(_logoImageSprite);
    
    return adLayer;
}

void NativeCustomViewScene::loadNativeAd(){
    
    // 広告のロードを実行します
    _nativeAdClient->loadAd([=](NendNativeAd* nativeAd, NendNativeLoadResultCode resultCode, std::string errorMessage) {
        if (resultCode == NEND_SUCCESS_LOAD_AD) {
            // ロード成功
            this->setAdElementsAndActivate(nativeAd);
        } else {
            // ロード失敗
            switch (resultCode) {
                case NEND_FAILED_TO_REQUEST:
                    // リクエスト失敗（通信エラー等）
                    break;
                case NEND_INVALID_RESPONSE_TYPE:
                    // SDK内部エラー
                    break;
                default:
                    break;
            }
            CCLOG("NativeAd load error. resultCode:%d, Message:%s",resultCode, errorMessage.c_str());
        }
    });
}

void NativeCustomViewScene::switchAutoReloadButtonCallback(Ref* pSender, Label* label)
{
    isAutoReload = !isAutoReload;
    if (isAutoReload) {
        // 広告の自動リロード開始
        _nativeAdClient->enableAutoReload(autoReloadInterval, [=](NendNativeAd* nativeAd, NendNativeLoadResultCode resultCode, std::string errorMessage) {
            if (resultCode == NEND_SUCCESS_LOAD_AD) {
                // ロード成功
                this->setAdElementsAndActivate(nativeAd);
            } else {
                // ロード失敗
                switch (resultCode) {
                    case NEND_FAILED_TO_REQUEST:
                        // リクエスト失敗（通信エラー等）
                        break;
                    case NEND_INVALID_RESPONSE_TYPE:
                        // SDK内部エラー
                        break;
                    default:
                        break;
                }
                CCLOG("NativeAd load error. resultCode:%d, Message:%s",resultCode, errorMessage.c_str());
            }
        });
        label->setString(stopAutoReloadStr);
    }
    else{
        // 広告の自動リロード停止
        _nativeAdClient->disableAutoReload();
        label->setString(startAutoReloadStr);
    }
}

void NativeCustomViewScene::setAdElementsAndActivate(nend_module::NendNativeAd* nativeAd){
    
    // 広告Nodeの各要素を設定します
    _prLabel->setString(nativeAd->prTextForAdvertisingExplicitly(NAD_NATIVE_ADVERTISING_EXPLIICITY_AD)); // 広告明示
    _shortTextLabel->setString(nativeAd->getShortText()); // 広告見出し
    _longTextLabel->setString(nativeAd->getLongText()); // 広告文
    _promotionNameLabel->setString(nativeAd->getPromotionNameText()); // プロモーション名
    _promotionURLLabel->setString(nativeAd->getPromotionUrlText()); // 表示URL
    _actionTextLabel->setString(nativeAd->getActionButtonText()); // アクションボタンテキスト
    // 広告画像のダウンロード
    nativeAd->downloadAdImage([=](Texture2D* adImageTexture, std::string errorMessage){
        if (nullptr != adImageTexture) {
            _adImageSprite->setTexture(adImageTexture);
            cocos2d::Rect rect = cocos2d::Rect();
            rect.size = adImageTexture->getContentSize();
            _adImageSprite->setTextureRect(rect);
        }
    });
    // ロゴ画像のダウンロード
    nativeAd->downloadLogoImage([=](Texture2D* adImageTexture, std::string errorMessage){
        if (nullptr != adImageTexture) {
            _logoImageSprite->setTexture(adImageTexture);
            cocos2d::Rect rect = cocos2d::Rect();
            rect.size = adImageTexture->getContentSize();
            _logoImageSprite->setTextureRect(rect);
        }
    });
    
    // 広告Nodeへクリックイベントの設定
    nativeAd->activateAdView(_adLayer, _prLabel);
    // イベント通知の callback を設定します
    nativeAd->setAdClickCallback([=](NendNativeAd *nativeAd, Node* node){
        // 広告表示クリック時
        CCLOG("Click ad.");
    });
}

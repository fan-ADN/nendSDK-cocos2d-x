//
//  NativeViewScene.cpp
//  CocosNendSample
//
//  Created by F@N Communications, Inc.
//
//

#include "NativeViewScene.h"
#include "NendNativeAdBinder.h"
#include "NativeMenuScene.h"
#include "NendNativeAdLog.h"

USING_NS_CC;
using namespace nend_module;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
const auto smallSquareApiKey = "10d9088b5bd36cf43b295b0774e5dcf7d20a4071";
const auto smallSquareSpotId = "485500";
const auto largeWideApiKey = "30fda4b3386e793a14b27bedb4dcd29f03d638e5";
const auto largeWideSpotId = "485504";
const auto textOnlyApiKey = "31e861edb574cfa0fb676ebdf0a0b9a0621e19fc";
const auto textOnlySpotId = "485507";
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
const auto smallSquareApiKey = "16cb170982088d81712e63087061378c71e8aa5c";
const auto smallSquareSpotId = "485516";
const auto largeWideApiKey = "a88c0bcaa2646c4ef8b2b656fd38d6785762f2ff";
const auto largeWideSpotId = "485520";
const auto textOnlyApiKey = "2b2381a116290c90b936e409482127efb7123dbc";
const auto textOnlySpotId = "485522";
#endif

typedef struct {
    std::string apiKey;
    std::string spotId;
}tSpotId;

const tSpotId spotIdArray[] = {
    {
        smallSquareApiKey,
        smallSquareSpotId
    },
    {
        largeWideApiKey,
        largeWideSpotId
    },
    {
        textOnlyApiKey,
        textOnlySpotId
    }
};


// native ad layout
const Size  dummySize = Size(0,0);
const Point dummyPoint = Point(0,0);

// Small-Square layout
const Size  smallSquareLayerSize = Size(300, 230);
const Point smallSquarePrLabelPoint = Point(252, 192);
const Size  smallSquarePrLabelSize = Size(40, 21);
const float smallSquarePrLabelFontSize = 14;
const Point smallSquareShortTextLabelPoint = Point(8, 182);
const Size  smallSquareShortTextLabelSize = Size(236, 40);
const float smallSquareShortTextLabelFontSize = 14;
const Point smallSquareLongTextLabelPoint = Point(96, 94);
const Size  smallSquareLongTextLabelSize = Size(196, 80);
const float smallSquareLongTextLabelFontSize = 14;
const Point smallSquarePromotionNameLabelPoint = Point(8, 65);
const Size  smallSquarePromotionNameLabelSize = Size(284, 21);
const float smallSquarePromotionNameLabelFontSize = 14;
const Point smallSquarePromotionURLLabelPoint = Point(8, 36);
const Size  smallSquarePromotionURLLabelSize = Size(284, 21);
const float smallSquarePromotionURLLabelFontSize = 14;
const Point smallSquareActionTextLabelPoint = Point(192, 8);
const Size  smallSquareActionTextLabelSize = Size(100, 21);
const float smallSquareActionTextLabelFontSize =14;
const Point smallSquareAdImageSpritePoint = Point(8, 94);

// Large-Wide layout
const Size  longWideLayerSize = Size(320, 380);
const Point longWidePrLabelPoint = Point(10, 8);
const Size  longWidePrLabelSize = Size(40, 21);
const float longWidePrLabelFontSize = 14;
const Point longWideShortTextLabelPoint = Point(10, 326);
const Size  longWideShortTextLabelSize = Size(254, 40);
const float longWideShortTextLabelFontSize = 14;
const Point longWideLongTextLabelPoint = Point(10, 95);
const Size  longWideLongTextLabelSize = Size(300, 35);
const float longWideLongTextLabelFontSize = 14;
const Point longWidePromotionNameLabelPoint = Point(10, 66);
const Size  longWidePromotionNameLabelSize = Size(300, 21);
const float longWidePromotionNameLabelFontSize = 14;
const Point longWidePromotionURLLabelPoint = Point(10, 37);
const Size  longWidePromotionURLLabelSize = Size(300, 21);
const float longWidePromotionURLLabelFontSize = 14;
const Point longWideActionTextLabelPoint = Point(210, 8);
const Size  longWideActionTextLabelSize = Size(100, 21);
const float longWideActionTextLabelFontSize =14;
const Point longWideAdImageSpritePoint = Point(10, 138);
const Point longWideLogoImageSpritePoint = Point(272, 326);

// Text-Only layout
const Size  textOnlyLayerSize = Size(300, 100);
const Point textOnlyPrLabelPoint = Point(252, 8);
const Size  textOnlyPrLabelSize = Size(40, 21);
const float textOnlyPrLabelFontSize = 14;
const Point textOnlyLongTextLabelPoint = Point(8, 35);
const Size  textOnlyLongTextLabelSize = Size(284, 60);
const float textOnlyLongTextLabelFontSize = 16;
const Point textOnlyActionTextLabelPoint = Point(8, 8);
const Size  textOnlyActionTextLabelSize = Size(100, 21);
const float textOnlyActionTextLabelFontSize =14;


// layout struct
typedef struct {
    Size  layerSize;
    Point prLabelPoint;
    Size  prLabelSize;
    float prLabelFontSize;
    Point shortTextLabelPoint;
    Size  shortTextLabelSize;
    float shortTextLabelFontSize;
    Point longTextLabelPoint;
    Size  longTextLabelSize;
    float longTextLabelFontSize;
    Point promotionNameLabelPoint;
    Size  promotionNameLabelSize;
    float promotionNameLabelFontSize;
    Point promotionURLLabelPoint;
    Size  promotionURLLabelSize;
    float promotionURLLabelFontSize;
    Point actionTextLabelPoint;
    Size  actionTextLabelSize;
    float actionTextLabelFontSize;
    Point imageSpritePoint;
    Point logoImageSpritePoint;
} tNativeAdLayout;

const tNativeAdLayout layoutArrays[] = {
    {
        smallSquareLayerSize ,
        smallSquarePrLabelPoint ,
        smallSquarePrLabelSize ,
        smallSquarePrLabelFontSize ,
        smallSquareShortTextLabelPoint ,
        smallSquareShortTextLabelSize ,
        smallSquareShortTextLabelFontSize ,
        smallSquareLongTextLabelPoint ,
        smallSquareLongTextLabelSize ,
        smallSquareLongTextLabelFontSize ,
        smallSquarePromotionNameLabelPoint ,
        smallSquarePromotionNameLabelSize ,
        smallSquarePromotionNameLabelFontSize ,
        smallSquarePromotionURLLabelPoint ,
        smallSquarePromotionURLLabelSize ,
        smallSquarePromotionURLLabelFontSize ,
        smallSquareActionTextLabelPoint ,
        smallSquareActionTextLabelSize ,
        smallSquareActionTextLabelFontSize ,
        smallSquareAdImageSpritePoint ,
        dummyPoint
    },
    {
        longWideLayerSize ,
        longWidePrLabelPoint ,
        longWidePrLabelSize ,
        longWidePrLabelFontSize ,
        longWideShortTextLabelPoint ,
        longWideShortTextLabelSize ,
        longWideShortTextLabelFontSize ,
        longWideLongTextLabelPoint ,
        longWideLongTextLabelSize ,
        longWideLongTextLabelFontSize ,
        longWidePromotionNameLabelPoint ,
        longWidePromotionNameLabelSize ,
        longWidePromotionNameLabelFontSize ,
        longWidePromotionURLLabelPoint ,
        longWidePromotionURLLabelSize ,
        longWidePromotionURLLabelFontSize ,
        longWideActionTextLabelPoint ,
        longWideActionTextLabelSize ,
        longWideActionTextLabelFontSize ,
        longWideAdImageSpritePoint ,
        longWideLogoImageSpritePoint
    },
    {
        textOnlyLayerSize ,
        textOnlyPrLabelPoint ,
        textOnlyPrLabelSize ,
        textOnlyPrLabelFontSize ,
        dummyPoint ,
        dummySize ,
        0 ,
        textOnlyLongTextLabelPoint ,
        textOnlyLongTextLabelSize ,
        textOnlyLongTextLabelFontSize ,
        dummyPoint ,
        dummySize ,
        0 ,
        dummyPoint ,
        dummySize ,
        0 ,
        textOnlyActionTextLabelPoint ,
        textOnlyActionTextLabelSize ,
        textOnlyActionTextLabelFontSize ,
        dummyPoint ,
        dummyPoint
    }
};


NativeType _nativeType;

NativeViewScene::NativeViewScene(){
}

NativeViewScene::~NativeViewScene(){
    // Scene 解放時に NendNativeAdClient, NendNativeAdBinder を解放します
    if (_binder) {
        delete _binder;
        _binder = nullptr;
    }
    if (_nativeAdClient) {
        delete _nativeAdClient;
        _nativeAdClient = nullptr;
    }
}

Scene* NativeViewScene::createScene(NativeType type)
{
    Scene* scene = Scene::create();
    NativeViewScene* layer = NativeViewScene::create();
    scene->addChild(layer);
    
    _nativeType = type;
    return scene;
}

bool NativeViewScene::init()
{
    if (!Layer::init()) {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();

    auto label = Label::createWithTTF("NativeAdViewScene", "fonts/Marker Felt.ttf", 24);
    label->setPosition(Point(origin.x + visibleSize.width/2,
                             origin.y + visibleSize.height - label->getContentSize().height));
    this->addChild(label, 1);

    auto showPreviousLabel = Label::createWithSystemFont("Back", "fonts/arial.ttf", 15);
    auto showPreviousItem = MenuItemLabel::create(showPreviousLabel, CC_CALLBACK_1(NativeViewScene::showPreviousSceneButtonCallback, this));
    auto showPreviousMenu = Menu::create(showPreviousItem, NULL);
    showPreviousMenu->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y - 210));
    this->addChild(showPreviousMenu);
    
    _adLayer = nullptr;
    _nativeAdClient = nullptr;
    _binder = nullptr;

    return true;
}

void NativeViewScene::onEnter()
{
    Layer::onEnter();
    
    // ネイティブ広告のログレベルを設定します
    NendNativeAdLog::setNativeLogLevel(NEND_NATIVE_LOG_LEVEL_DEBUG);
    this->makeAndLoadNativeAd();
}

void NativeViewScene::onExit()
{
    Layer::onExit();
}


void NativeViewScene::showPreviousSceneButtonCallback(Ref* pSender)
{
    Director::getInstance()->replaceScene(TransitionSlideInL::create(0.5f,NativeMenuScene::createScene()));
}

void NativeViewScene::makeAndLoadNativeAd(){

    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    _adLayer = this->makeNativeAdLayer();
    _adLayer->setPosition(Point((visibleSize.width - _adLayer->getContentSize().width) /2, (visibleSize.height - _adLayer->getContentSize().height) /2));
    this->addChild(_adLayer);
    
    this->loadNativeAd();
}

LayerColor * NativeViewScene::makeNativeAdLayer()
{
    auto layout = layoutArrays[_nativeType];
    
    // ネイティブ広告を表示する領域を作成します
    auto adLayer = LayerColor::create(Color4B::WHITE, layout.layerSize.width, layout.layerSize.height);
    
    // 広告要素を作成し 上記で作成した領域に配置します

    // 広告明示
    auto prLabel = Label::create();
    prLabel->setName("NendNativeAdPrLabel"); // 広告要素の識別に使用する任意の名前を設定します
    prLabel->setTextColor(Color4B::BLACK);
    prLabel->setAnchorPoint(Point(0,0));
    prLabel->setPosition(layout.prLabelPoint);
    prLabel->setWidth(layout.prLabelSize.width);
    prLabel->setHeight(layout.prLabelSize.height);
    prLabel->setSystemFontSize(layout.prLabelFontSize);
    adLayer->addChild(prLabel);
    
    // 広告見出し
    auto shortTextLabel = Label::create();
    shortTextLabel->setTextColor(Color4B::BLACK);
    shortTextLabel->setAnchorPoint(Point(0,0));
    shortTextLabel->setName("NendNativeAdShortTextLabel"); // 広告要素の識別に使用する任意の名前を設定します
    shortTextLabel->setPosition(layout.shortTextLabelPoint);
    shortTextLabel->setWidth(layout.shortTextLabelSize.width);
    shortTextLabel->setHeight(layout.shortTextLabelSize.height);
    shortTextLabel->setSystemFontSize(layout.shortTextLabelFontSize);
    adLayer->addChild(shortTextLabel);
    
    // 広告文
    auto longTextLabel = Label::create();
    longTextLabel->setName("NendNativeAdLongTextLabel"); // 広告要素の識別に使用する任意の名前を設定します
    longTextLabel->setTextColor(Color4B::BLACK);
    longTextLabel->setAnchorPoint(Point(0,0));
    longTextLabel->setPosition(layout.longTextLabelPoint);
    longTextLabel->setWidth(layout.longTextLabelSize.width);
    longTextLabel->setHeight(layout.longTextLabelSize.height);
    longTextLabel->setSystemFontSize(layout.longTextLabelFontSize);
    adLayer->addChild(longTextLabel);
    
    // プロモーション名
    auto promotionNameLabel = Label::create();
    promotionNameLabel->setName("NendNativeAdPromotionNameLabel"); // 広告要素の識別に使用する任意の名前を設定します
    promotionNameLabel->setTextColor(Color4B::BLACK);
    promotionNameLabel->setAnchorPoint(Point(0,0));
    promotionNameLabel->setPosition(layout.promotionNameLabelPoint);
    promotionNameLabel->setWidth(layout.promotionNameLabelSize.width);
    promotionNameLabel->setHeight(layout.promotionNameLabelSize.height);
    promotionNameLabel->setSystemFontSize(layout.promotionNameLabelFontSize);
    adLayer->addChild(promotionNameLabel);

    // プロモーションURL
    auto promotionURLLabel = Label::create();
    promotionURLLabel->setName("NendNativeAdPromotionURLLabel"); // 広告要素の識別に使用する任意の名前を設定します
    promotionURLLabel->setTextColor(Color4B::BLACK);
    promotionURLLabel->setAnchorPoint(Point(0,0));
    promotionURLLabel->setPosition(layout.promotionURLLabelPoint);
    promotionURLLabel->setWidth(layout.promotionURLLabelSize.width);
    promotionURLLabel->setHeight(layout.promotionURLLabelSize.height);
    promotionURLLabel->setSystemFontSize(layout.promotionURLLabelFontSize);
    adLayer->addChild(promotionURLLabel);
    
    // アクションボタン
    auto actionTextLabel = Label::create();
    actionTextLabel->setName("NendNativeAdActionTextLabel"); // 広告要素の識別に使用する任意の名前を設定します
    actionTextLabel->setTextColor(Color4B::BLUE);
    actionTextLabel->setAnchorPoint(Point(0,0));
    actionTextLabel->setPosition(layout.actionTextLabelPoint);
    actionTextLabel->setWidth(layout.actionTextLabelSize.width);
    actionTextLabel->setHeight(layout.actionTextLabelSize.height);
    actionTextLabel->setSystemFontSize(layout.actionTextLabelFontSize);
    actionTextLabel->setTextColor(Color4B::BLUE);
    adLayer->addChild(actionTextLabel);
    
    // 広告画像
    auto adImageSprite = Sprite::create();
    adImageSprite->setName("NendNativeAdImageSprite"); // 広告要素の識別に使用する任意の名前を設定します
    adImageSprite->setAnchorPoint(Point(0,0));
    if (_nativeType != NATIVE_LARGE_WIDE) {
        adImageSprite->setPosition(layout.imageSpritePoint);
        adLayer->addChild(adImageSprite);
    } else {
        // 広告画像(クリップ)
        auto clipNode = NendNativeClippingNode::create(Size(300.f, 180.f), 10.f, adImageSprite, NEND_CLIP_CENTER);
        clipNode->setName("NendNativeAdClipNode");
        clipNode->setPosition(layout.imageSpritePoint);
        clipNode->addChild(adImageSprite);
        adLayer->addChild(clipNode);
    }

    // ロゴ画像
    auto logoImageSprite = Sprite::create();
    logoImageSprite->setAnchorPoint(Point(0,0));
    logoImageSprite->setName("NendNativeAdLogoImageSprite"); // 広告要素の識別に使用する任意の名前を設定します
    logoImageSprite->setPosition(layout.logoImageSpritePoint);
    adLayer->addChild(logoImageSprite);
    
    return adLayer;
}

void NativeViewScene::loadNativeAd(){
    
    // NendNativeAdClient クラスのインスタンスを生成します
    auto apiKey = spotIdArray[_nativeType].apiKey;
    auto spotId = spotIdArray[_nativeType].spotId;
    _nativeAdClient = new NendNativeAdClient(apiKey, spotId);

    // 広告のロードを実行します
    _nativeAdClient->loadAd([=](NendNativeAd* nativeAd, NendNativeLoadResultCode resultCode, std::string errorMessage) {
        if (resultCode == NEND_SUCCESS_LOAD_AD) {
            // ロード成功
            // 広告要素と表示するNodeの紐付けを行います
            _binder = new NendNativeAdBinder();
            
            // 前項でLabelやSpriteにセットした識別用の名前を設定します
            _binder->setPrText_Name("NendNativeAdPrLabel"); // 広告明示
            _binder->setShortTitle_Name("NendNativeAdShortTextLabel"); // 広告見出し
            _binder->setLongText_Name("NendNativeAdLongTextLabel"); // 広告文
            _binder->setPromotionName_Name("NendNativeAdPromotionNameLabel"); // プロモーション名
            _binder->setPromotionUrl_Name("NendNativeAdPromotionURLLabel"); // プロモーションURL
            _binder->setActionText_Name("NendNativeAdActionTextLabel"); // アクションボタン
            _binder->setAdImage_Name("NendNativeAdImageSprite"); // 広告画像
            if (_nativeType == NATIVE_LARGE_WIDE) {
                _binder->setLogoImage_Name("NendNativeAdLogoImageSprite"); // ロゴ画像
            }
            // ロードした広告の描画を行います
            // 第一引数には広告要素がレイアウトされたNodeを設定します
            nativeAd->renderAdViews(_adLayer, _binder, NAD_NATIVE_ADVERTISING_EXPLIICITY_PR);

            // イベント通知の callback を設定します
            nativeAd->setAdClickCallback([=](NendNativeAd *nativeAd, Node* node){
                // 広告表示クリック時
                CCLOG("Click ad.");
            });

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

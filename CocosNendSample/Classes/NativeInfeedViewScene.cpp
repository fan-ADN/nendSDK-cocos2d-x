//
//  NativeInfeedViewScene.cpp
//  CocosNendSample
//
//  Created by F@N Communications, Inc.
//
//

#include "NativeInfeedViewScene.h"
#include "NativeMenuScene.h"
#include "NendNativeAdLog.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace nend_module;

typedef enum {
    CELL_LABEL_TAG,
    CELL_AD_TAG
} CellTag;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
const auto apiKey = "10d9088b5bd36cf43b295b0774e5dcf7d20a4071";
const auto spotId = "485500";
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
const auto apiKey = "16cb170982088d81712e63087061378c71e8aa5c";
const auto spotId = "485516";
#endif

const int numberOfCells = 20; // cellの総数
const int adRepeatInterval = 5; // 広告の表示間隔
NendNativeAdClient* m_adClient;
std::vector<LayerColor*> m_adlayers;


Scene* NativeInfeedViewScene::createScene()
{
    Scene* scene = Scene::create();
    NativeInfeedViewScene* layer = NativeInfeedViewScene::create();
    scene->addChild(layer);
    
    return scene;
}

NativeInfeedViewScene::NativeInfeedViewScene()
{
}

NativeInfeedViewScene::~NativeInfeedViewScene()
{
    if (m_adClient) {
        delete m_adClient;
        m_adClient = nullptr;
    }

    for (auto itl = m_adlayers.begin(); itl != m_adlayers.end(); ++itl) {
        auto layout = *itl;
        layout->release();
    }
    m_adlayers.clear();
}

bool NativeInfeedViewScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();

    auto label = Label::createWithTTF("NativeInfeedViewScene", "fonts/Marker Felt.ttf", 18);
    label->setPosition(Point(origin.x + visibleSize.width/2,
                             origin.y + visibleSize.height - label->getContentSize().height));
    this->addChild(label, 1);

    auto showPreviousLabel = Label::createWithSystemFont("Back", "fonts/arial.ttf", 12);
    auto showPreviousItem = MenuItemLabel::create(showPreviousLabel, CC_CALLBACK_1(NativeInfeedViewScene::showPreviousSceneButtonCallback, this));
    auto showPreviousMenu = Menu::create(showPreviousItem, NULL);
    showPreviousMenu->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y - 200));
    this->addChild(showPreviousMenu);

    NendNativeAdLog::setNativeLogLevel(NEND_NATIVE_LOG_LEVEL_DEBUG);
    createNativeAdView();

    TableView* tableView = TableView::create(this, Size(visibleSize.width, visibleSize.height - 110));
    tableView->setDirection(TableView::Direction::VERTICAL);
    tableView->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);
    tableView->setDelegate(this);
    tableView->setPosition(Point(0, 65));
    addChild(tableView);
    tableView->reloadData();

    return true;
}

void NativeInfeedViewScene::onEnter()
{
    Layer::onEnter();
}

void NativeInfeedViewScene::onExit()
{
    Layer::onExit();
}

#pragma mark - button callback
void NativeInfeedViewScene::showPreviousSceneButtonCallback(Ref* pSender)
{
    Director::getInstance()->replaceScene(TransitionSlideInL::create(0.5f,NativeMenuScene::createScene()));
}

#pragma mark - create NativeAd
void NativeInfeedViewScene::createNativeAdView()
{
    // NendNativeAdClient生成
    m_adClient = new NendNativeAdClient(apiKey, spotId);

    m_adlayers.clear();

    for (int i = 0; i < numberOfCells / adRepeatInterval; i+=1) {
        
        // 広告描画領域作成
        Size visibleSize = Director::getInstance()->getVisibleSize();
        
        // 広告View
        LayerColor* adLayer;
        adLayer = LayerColor::create(Color4B::WHITE, visibleSize.width, 48);
        adLayer->setName("adlayer");
        adLayer->retain();
        
        // 広告明示
        auto prLabel = Label::create();
        prLabel->setName("prText");
        prLabel->setPosition(Point(visibleSize.width - 40, 10));
        prLabel->setSystemFontSize(10);
        prLabel->setTextColor(Color4B::RED);
        adLayer->addChild(prLabel);
        
        // 広告見出し
        auto shortLabel = Label::create();
        shortLabel->setName("shortText");
        shortLabel->setPosition(Point(5 + visibleSize.width / 2, 30));
        shortLabel->setWidth(visibleSize.width - 70);
        shortLabel->setSystemFontSize(10);
        shortLabel->setTextColor(Color4B::BLACK);
        adLayer->addChild(shortLabel);
        
        // アクションボタン
        auto actionLabel = Label::create();
        actionLabel->setName("actionText");
        actionLabel->setPosition(Point(80, 10));
        actionLabel->setSystemFontSize(10);
        actionLabel->setTextColor(Color4B::BLUE);
        adLayer->addChild(actionLabel);
        
        // 広告画像
        auto adImageSprite = Sprite::create();
        adImageSprite->setName("adImage");
        adImageSprite->setScale(0.4);
        adImageSprite->setPosition(Point(20, 24));
        adLayer->addChild(adImageSprite);
        m_adlayers.push_back(adLayer);
        
        m_adClient->loadAd([=](nend_module::NendNativeAd* nativeAd, NendNativeLoadResultCode resultCode, std::string errorMessage){
            switch (resultCode) {
                case NEND_SUCCESS_LOAD_AD:
                    CCLOG("NEND_SUCCESS_LOAD_AD:%d",resultCode);
                    prLabel->setString(nativeAd->prTextForAdvertisingExplicitly(NAD_NATIVE_ADVERTISING_EXPLIICITY_PR));
                    shortLabel->setString(nativeAd->getShortText());
                    actionLabel->setString(nativeAd->getActionButtonText());
                    nativeAd->downloadAdImage([=](Texture2D* texture, std::string errorMessage){
                        if (texture != nullptr) {
                            adImageSprite->setTexture(texture);
                            cocos2d::Rect rect = cocos2d::Rect();
                            rect.size = texture->getContentSize();
                            adImageSprite->setTextureRect(rect);
                        }
                        else {
                            CCLOG("Ad image download error. Error message:%s", errorMessage.c_str());
                        }
                    });
                    nativeAd->activateAdView(adLayer, prLabel);
                    nativeAd->setAdClickCallback([=](nend_module::NendNativeAd* Ad, Node* container){
                        CCLOG("Click ad.");
                    });
                    break;
                case NEND_FAILED_TO_REQUEST:
                    CCLOG("NEND_FAILED_TO_REQUEST:%d:%s",resultCode, errorMessage.c_str());
                    break;
                case NEND_INVALID_RESPONSE_TYPE:
                    CCLOG("NEND_INVALID_RESPONSE_TYPE:%d:%s",resultCode, errorMessage.c_str());
                    break;
                default:
                    break;
            }
        });

    }
}

#pragma mark - TableViewDataSource
TableViewCell* NativeInfeedViewScene::tableCellAtIndex(TableView* table, ssize_t idx)
{
    Size winSize = Director::getInstance()->getWinSize();
    
    TableViewCell *cell;
    int cell_tag = CELL_LABEL_TAG;
    
    if (idx % adRepeatInterval == adRepeatInterval-1) {
        cell_tag = CELL_AD_TAG;
    }
    
    do {
        cell = table->dequeueCell();
        if (cell != nullptr && cell->getTag() == cell_tag) {
            break;
        }
    }while (cell);
    
    if (cell) {
        auto oldAdLayer = dynamic_cast<LayerColor*>(cell->getChildByTag(102));
        if (oldAdLayer) {
            oldAdLayer->removeFromParentAndCleanup(false);
        }

        if (cell_tag == CELL_AD_TAG) {
            auto adLayer = m_adlayers[idx / adRepeatInterval];
            cell->addChild(adLayer, 0, 102);
        } else if (cell_tag == CELL_LABEL_TAG){
            auto rowLabel = dynamic_cast<Label*>(cell->getChildByTag(2));
            if (rowLabel && idx % adRepeatInterval != adRepeatInterval-1) {
                rowLabel->setString(StringUtils::format("Row index:%zd", idx));
            }
        }
    } else {
        cell = new TableViewCell();
        cell->autorelease();

        if (cell_tag == CELL_AD_TAG) {
            if (idx % adRepeatInterval == adRepeatInterval-1) {
                auto adLayer = m_adlayers[idx / adRepeatInterval];
                cell->addChild(adLayer, 0, 102);
            }
        } else if (cell_tag == CELL_LABEL_TAG) {
            
            // cell background
            Sprite* bg = Sprite::create();
            bg->setAnchorPoint(Point(0, 0));
            bg->setTextureRect(Rect(0, 0, winSize.width, 48));
            bg->setColor(Color3B::GRAY);
            cell->addChild(bg);
            
            // border line
            auto line = Sprite::create();
            line->setAnchorPoint(Vec2(0, 0));
            line->setTextureRect(Rect(0, 0, winSize.width, 1));
            line->setColor(Color3B(100,100,100));
            cell->addChild(line);
            
            // cell text
            auto rowText = StringUtils::format("Row index:%zd", idx);
            auto rowLabel = Label::createWithSystemFont(rowText.c_str(), "Arial", 12);
            rowLabel->setAnchorPoint(Vec2(0.5, 0.5));
            rowLabel->setPosition(Vec2(winSize.width/2, 48/2));
            rowLabel->setColor(Color3B::BLACK);
            cell->addChild(rowLabel, 0, 2);
        }

        cell->setTag(cell_tag);
    }

    return cell;
}

ssize_t NativeInfeedViewScene::numberOfCellsInTableView(TableView* table)
{
    return numberOfCells;
}

cocos2d::Size NativeInfeedViewScene::cellSizeForTable(TableView* table)
{
    return Size(200, 48);
}

#pragma mark - TableViewDelegate
void NativeInfeedViewScene::tableCellTouched(TableView* table, TableViewCell* cell)
{
}

#pragma mark - ScrollViewDelegate
void NativeInfeedViewScene::scrollViewDidScroll(ScrollView* view)
{
}

void NativeInfeedViewScene::scrollViewDidZoom(ScrollView* view)
{
}

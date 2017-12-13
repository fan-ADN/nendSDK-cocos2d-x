//
//  NativeInfeedViewScene.hpp
//  CocosNendSample
//
//  Created by F@N Communications, Inc.
//
//

#ifndef NativeInfeedViewScene_h
#define NativeInfeedViewScene_h

#include "cocos2d.h"
#include "cocos-ext.h"
#include "NendNativeAdClient.h"

class NativeInfeedViewScene : public cocos2d::Scene, public cocos2d::extension::TableViewDelegate, public cocos2d::extension::TableViewDataSource
{
private:
    void createTableView();
    void createNativeAdView();
    void showPreviousSceneButtonCallback(cocos2d::Ref* pSender);
public:
    static cocos2d::Scene* createScene();
    NativeInfeedViewScene();
    ~NativeInfeedViewScene();
    
    virtual bool init();
    void onEnter();
    void onExit();

    CREATE_FUNC(NativeInfeedViewScene);

    // TableViewDataSource
    virtual cocos2d::extension::TableViewCell* tableCellAtIndex(cocos2d::extension::TableView* table, ssize_t idx);
    virtual ssize_t numberOfCellsInTableView(cocos2d::extension::TableView* table);
    virtual cocos2d::Size cellSizeForTable(cocos2d::extension::TableView* table);

    // ScrollViewDelegate
    virtual void scrollViewDidScroll(cocos2d::extension::ScrollView* view);
    virtual void scrollViewDidZoom(cocos2d::extension::ScrollView* view);

    // TableViewDelegate
    virtual void tableCellTouched(cocos2d::extension::TableView* table, cocos2d::extension::TableViewCell* cell);


};
#endif /* NativeInfeedViewScene_h */

//
//  NendModule.mm
//
//  Created by F@N Communications, Inc.
//
//

#include "NendModule.h"
#include "AppController.h"
#import "RootViewController.h"
#import "NADView.h"

@interface NadViewDelegate : NSObject<NADViewDelegate>
{
}
@end

@implementation NadViewDelegate

#pragma mark - NADViewDelegateの設定

// 初回ロード終了後の処理を記述
-(void)nadViewDidFinishLoad:(NADView *)adView{
    NendModule::sendEventDispatcher(FINISH_LOAD_AD);
    NendModule::layoutNADView();
}

// 広告受信成功後処理を記述
-(void)nadViewDidReceiveAd:(NADView *)adView{
    NendModule::sendEventDispatcher(RECEIVE_AD);
}

// 広告受信失敗の処理を記述
-(void)nadViewDidFailToReceiveAd:(NADView *)adView{
    NendModule::sendEventDispatcher(FAIL_TO_RECEIVE_AD);
}

// 広告クリック時の処理を記述
-(void)nadViewDidClickAd:(NADView *)adView{
    NendModule::sendEventDispatcher(CLICK_AD);
}

@end

#pragma mark -
//シングルトンの設定
NendModule* NendModule::m_mySingleton = NULL;
NADView* nadView = nil;
NSString* nendIDString = nil;
NSString* spotIDString = nil;
NADViewLayoutType layoutType = TOP;
cocos2d::Point newPos;
NendModule::NendModule()
{
    
}

#pragma mark -
NendModule* NendModule::sharedNendModule(){
    
    if (NULL == m_mySingleton) {
        //クラス未生成の場合は生成する
        m_mySingleton = new NendModule();
    }
    
    return m_mySingleton;
}

#pragma mark - NADView生成、API Key, NendIDを設定
void NendModule::createNADView(char* apiKey, char* spotID, bool isAdjust){
    if(nadView){
        // すでにNADViewを生成済み
        return;
    }
    
    NendModule::sharedNendModule();
    
    //NADViewの生成
    nadView = [[NADView alloc] initWithIsAdjustAdSize:isAdjust];
    
    //NADViewDelegateクラスを生成
    nadView.delegate = (id<NADViewDelegate>)[[NadViewDelegate alloc] init];
    
    AppController* app = [UIApplication sharedApplication].delegate;
    RootViewController* viewController = app.viewController;
    [viewController.view addSubview:nadView];
    
    nendIDString = [NSString stringWithCString:apiKey encoding:NSUTF8StringEncoding];
    spotIDString = [NSString stringWithCString:spotID encoding:NSUTF8StringEncoding];
    
    [nadView setNendID:nendIDString spotID:spotIDString];
}

#pragma mark - NADView生成、API Key, NendID、位置を設定
void NendModule::createNADView(char* apiKey, char* spotID, cocos2d::Point pos){
    
    NendModule::createNADView(apiKey, spotID, pos, false);
}

void NendModule::createNADView(char* apiKey, char* spotID, cocos2d::Point pos, bool isAdjust){
    
    NendModule::createNADView(apiKey, spotID, isAdjust);
    
    layoutType = USER;
    newPos = pos;
    
    NendModule::load();
}

#pragma mark - NADView生成、画面上部、API Key, NendIDを設定
void NendModule::createNADViewTop(char *apiKey, char *spotID){
    
    NendModule::createNADViewTop(apiKey, spotID, false);
}

void NendModule::createNADViewTop(char *apiKey, char *spotID, bool isAdjust){
    
    NendModule::createNADView(apiKey, spotID, isAdjust);
    
    layoutType = TOP;
    
    NendModule::load();
}

#pragma mark - NADView生成、画面下部、API Key, NendIDを設定
void NendModule::createNADViewBottom(char *apiKey, char *spotID){
    NendModule::createNADViewBottom(apiKey, spotID, false);
}

void NendModule::createNADViewBottom(char *apiKey, char *spotID, bool isAdjust){
    
    NendModule::createNADView(apiKey, spotID, isAdjust);
    
    layoutType = BOTTOM;
    
    NendModule::load();
}

#pragma mark - setPositionTop
//NADViewを画面上部・中央に移動する
void setPositionTop(){
    if (!nadView) {
        return;
    }
    //Windowサイズを取得
    auto view = cocos2d::Director::getInstance()->getOpenGLView();
    UIView *baseView = (UIView *) view->getEAGLView();
    CGRect mainViewRect = baseView.bounds;
    
    //NADViewの位置を変更
    [nadView setFrame:CGRectMake((mainViewRect.size.width - nadView.frame.size.width) /2, 0, nadView.frame.size.width, nadView.frame.size.height)];
    
}

#pragma mark - setPositionButtom
//NADViewを画面下部・中央に移動する
void setPositionButtom(){
    if (!nadView) {
        return;
    }
    auto view = cocos2d::Director::getInstance()->getOpenGLView();
    UIView *baseView = (UIView *) view->getEAGLView();
    CGRect mainViewRect = baseView.bounds;
    
    [nadView setFrame:CGRectMake((mainViewRect.size.width - nadView.frame.size.width) /2, mainViewRect.size.height - nadView.frame.size.height, nadView.frame.size.width, nadView.frame.size.height)];
    
}

#pragma mark - setPositionUser
//NADViewを指定位置に配置する
void setPositionUser() {
    if (!nadView) {
        return;
    }
    //cocos2d-x上の座標をiOSの座標に変換
    //cocos2d-xで管理するwindowサイズを取得
    cocos2d::Size size = Director::getInstance()->getWinSize();
    
    //座標を割合で取得
    cocos2d::Point pointRate;
    pointRate.x = (newPos.x / size.width);
    pointRate.y = (newPos.y / size.height);
    
    //iOSで管理するViewのサイズを取得
    auto view = cocos2d::Director::getInstance()->getOpenGLView();
    UIView *baseView = (UIView *) view->getEAGLView();
    CGRect mainViewRect = baseView.bounds;
    
    //高さをiOS基準に変換する
    CGPoint newPosition;
    newPosition.x = mainViewRect.size.width * pointRate.x;
    newPosition.y = mainViewRect.size.height - (mainViewRect.size.height * pointRate.y);
    
    //座標の設定
    [nadView setFrame:CGRectMake(newPosition.x, newPosition.y, nadView.frame.size.width, nadView.frame.size.height)];
    
}

#pragma mark - NADViewの表示位置を調整する
void NendModule::layoutNADView() {
    switch (layoutType) {
        case TOP:
            setPositionTop();
            break;
        case BOTTOM:
            setPositionButtom();
            break;
        case USER:
            setPositionUser();
            break;
        default:
            break;
    }
}

#pragma mark - NADView非表示
void NendModule::hideNADView(){
    if (nadView) {
        [nadView setHidden:YES];
    }
}

#pragma mark - NADView再表示
void NendModule::showNADView(){
    if (nadView) {
        [nadView setHidden:NO];
    }
}

#pragma mark - load
void NendModule::load(){
    if (nadView) {
        [nadView load];
    }
}

#pragma mark - pause
void NendModule::pause(){
    if (nadView) {
        [nadView pause];
    }
}

#pragma mark - resume
void NendModule::resume(){
    if (nadView) {
        [nadView resume];
    }
}

#pragma mark - release
void NendModule::release(){
    NendModule::pause();
    if (nadView) {
        [nadView.delegate release];
        nadView.delegate = nil;
        [nadView removeFromSuperview];
        [nadView release];
        nadView = nil;
    }
}

#pragma mark - sendEventDispatcher
void NendModule::sendEventDispatcher(int resultCode){
    Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(NADViewDelegateNotification,&resultCode);
}

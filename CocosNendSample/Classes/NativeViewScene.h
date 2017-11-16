//
//  NativeViewScene.h
//  CocosNendSample
//
//  Created by F@N Communications, Inc.
//
//

#ifndef NativeViewScene_h
#define NativeViewScene_h

#include "cocos2d.h"
#include "NendNativeAdClient.h"

typedef enum {
    NATIVE_SMALL_SQUARE,
    NATIVE_LARGE_WIDE,
    NATIVE_TEXT_ONLY
} NativeType;

class NativeViewScene : public cocos2d::Layer
{
private:
    void showPreviousSceneButtonCallback(cocos2d::Ref* pSender);
    void makeAndLoadNativeAd();
    cocos2d::LayerColor * makeNativeAdLayer();
    void loadNativeAd();
    // インスタンスをクラス内で保持します
    nend_module::NendNativeAdClient* _nativeAdClient;
    nend_module::NendNativeAdBinder* _binder;
    LayerColor* _adLayer;
public:
    NativeViewScene();
    ~NativeViewScene();
    static cocos2d::Scene* createScene(NativeType type);
    
    virtual bool init();
    void onEnter();
    void onExit();

    CREATE_FUNC(NativeViewScene);
};

#endif /* NativeViewScene_h */

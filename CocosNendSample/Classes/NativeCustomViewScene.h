//
//  NativeCustomViewScene.h
//  CocosNendSample
//
//  Created by F@N Communications, Inc.
//
//

#ifndef NativeCustomViewScene_h
#define NativeCustomViewScene_h

#include "cocos2d.h"
#include "NendNativeAdClient.h"

class NativeCustomViewScene : public cocos2d::Layer
{
private:
    void makeAndLoadNativeAd();
    cocos2d::LayerColor * makeNativeAdLayer();
    void loadNativeAd();
    void setAdElementsAndActivate(nend_module::NendNativeAd* ad);
    // インスタンスをクラス内で保持します
    nend_module::NendNativeAdClient* _nativeAdClient;

    LayerColor* _adLayer;
    cocos2d::Label *_prLabel;
    cocos2d::Label *_shortTextLabel;
    cocos2d::Label *_longTextLabel;
    cocos2d::Label *_promotionNameLabel;
    cocos2d::Label *_promotionURLLabel;
    cocos2d::Label *_actionTextLabel;
    cocos2d::Sprite *_adImageSprite;
    cocos2d::Sprite *_logoImageSprite;

    void showPreviousSceneButtonCallback(cocos2d::Ref* pSender);
    void switchAutoReloadButtonCallback(cocos2d::Ref* pSender, cocos2d::Label* label);
public:
    NativeCustomViewScene();
    ~NativeCustomViewScene();
    static cocos2d::Scene* createScene();
    
    virtual bool init();
    
    CREATE_FUNC(NativeCustomViewScene);
};

#endif /* NativeCustomViewScene_h */

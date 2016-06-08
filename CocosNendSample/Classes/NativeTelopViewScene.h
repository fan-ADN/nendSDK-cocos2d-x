//
//  NativeTelopViewScene.hpp
//  CocosNendSample
//

#ifndef NativeTelopViewScene_h
#define NativeTelopViewScene_h

#include "cocos2d.h"
#include "NendNativeAdClient.h"
#include "NendNativeAdBinder.h"

class NativeTelopViewScene : public cocos2d::Layer
{
private:
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    void scroll();
    void scrollFinished(Node* sender);
    
    cocos2d::Node* _adNode;
    cocos2d::Sprite* _adImage;
    cocos2d::Label* _prText;
    cocos2d::Label* _shortText;
    nend_module::NendNativeAdClient* _client;
    nend_module::NendNativeAdBinder* _binder;
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(NativeTelopViewScene);

    ~NativeTelopViewScene();
    
    void onEnter();
    void onExit();
};

#endif /* NativeTelopViewScene_h */
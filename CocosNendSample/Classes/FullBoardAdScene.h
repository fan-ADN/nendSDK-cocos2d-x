//
//  FullBoardAdScene.h
//  CocosNendSample
//

#ifndef FullBoardAdScene_h
#define FullBoardAdScene_h

#include "NendFullBoardAd.h"

class FullBoardAdScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    
    virtual bool init();
    
    CREATE_FUNC(FullBoardAdScene);
private:
    cocos2d::MenuItemLabel* _status;
    nend_module::NendFullBoardAd* _ad;
    void menuLoadAdCallback(cocos2d::Ref* pSender);
    void menuShowAdCallback(cocos2d::Ref* pSender);
    void menuCloseCallback(cocos2d::Ref* pSender);
};

#endif /* FullBoardAdScene_h */

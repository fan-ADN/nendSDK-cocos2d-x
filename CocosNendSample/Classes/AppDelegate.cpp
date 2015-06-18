#include "AppDelegate.h"
#include "HelloWorldScene.h"
#include "NendModule.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "NendIconModule.h"
#endif

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

//if you want a different context,just modify the value of glContextAttrs
//it will takes effect on all platforms
void AppDelegate::initGLContextAttrs()
{
    //set OpenGL context attributions,now can only set six attributions:
    //red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
}

// If you want to use packages manager to install more packages, 
// don't modify or remove this function
static int register_all_packages()
{
    return 0; //flag for packages manager
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLViewImpl::create("My Game");
        director->setOpenGLView(glview);
    }
    
    auto frameSize = glview->getFrameSize();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    
    if (frameSize.width > 320) {
        // retina
        
        if (frameSize.width >= 1024) {
            
            director->setContentScaleFactor(3.f);
            
        }else{
            
            director->setContentScaleFactor(2.f);
        }
        
    }else{
        // none retina
        director->setContentScaleFactor(1.f);
    }
    
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    
    if (frameSize.width > 480) {

        if (frameSize.width >= 1024) {

            director->setContentScaleFactor(3.f);

        }else{

            director->setContentScaleFactor(2.f);
        }

    }else{
        director->setContentScaleFactor(1.f);
    }

#endif

    glview->setDesignResolutionSize(frameSize.width, frameSize.height, ResolutionPolicy::SHOW_ALL);

    // turn on display FPS
    director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

    register_all_packages();

    // create a scene. it's an autorelease object
    auto scene = HelloWorld::createScene();

    // run
    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // アプリがバックグラウンドになった時に定期ロードを停止する
    NendModule::pause();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    NendIconModule::pause();
#endif
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // アプリがフォアグラウンドになった時に定期ロードを再開する
    NendModule::resume();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    NendIconModule::resume();
#endif
}

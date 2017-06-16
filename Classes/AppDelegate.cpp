#include "AppDelegate.h"
#include "SplashScene.h"
#include "Definitions.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	#ifdef SDKBOX_ENABLED
		#include "PluginAdMob/PluginAdMob.h"
		using namespace sdkbox;
	#endif
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

bool AppDelegate::applicationDidFinishLaunching() {

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	#ifdef SDKBOX_ENABLED	
		sdkbox::PluginAdMob::init();
	#endif
#endif

    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
		glview = GLViewImpl::createWithRect("EASYMATHS", Rect(0, 0, GAME_SCREEN_WIDTH/2, GAME_SCREEN_HEIGHT/2));
        director->setOpenGLView(glview);
    }

	director->getOpenGLView()->setDesignResolutionSize(GAME_SCREEN_WIDTH, GAME_SCREEN_HEIGHT, ResolutionPolicy::EXACT_FIT);

    // turn on display FPS
    director->setDisplayStats(false);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval((float)1.0 / 60);

    FileUtils::getInstance()->addSearchPath("res");

    // create a scene. it's an autorelease object
    auto scene = SplashScene::createScene();

    // run
    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}

#include "GameOverLayer.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "Definitions.h"
#include "MainMenuScene.h"		
#include "GameScene.h"

USING_NS_CC;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#ifdef SDKBOX_ENABLED
#include "PluginAdMob/PluginAdMob.h"
using namespace sdkbox;
#endif
#endif

using namespace cocostudio::timeline;



// on "init" you need to initialize your instance
bool GameOverLayer::init()
{

    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto rootNode = CSLoader::createNode("GameOverLayer.csb");
	this->addChild(rootNode);

	btnRetry = (cocos2d::ui::Button *)rootNode->getChildByName("btnRetry");
	btnRetry->addTouchEventListener(CC_CALLBACK_2(GameOverLayer::eventButonRetryTouch, this));

	btnGoHome = (cocos2d::ui::Button *)rootNode->getChildByName("btnGoHome");
	btnGoHome->addTouchEventListener(CC_CALLBACK_2(GameOverLayer::eventButtonHomeTouch, this));

	lblScore = (cocos2d::ui::Text *)rootNode->getChildByName("lblScore");
	lblHigh = (cocos2d::ui::Text *)rootNode->getChildByName("lblHigh");



#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#ifdef SDKBOX_ENABLED	
	sdkbox::PluginAdMob::cache("home");
	sdkbox::PluginAdMob::show("home");
#endif
#endif


    return true;
}


void GameOverLayer::gotoMainMenuScene(){
	auto scene = MainMenuScene::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(TRAINDITION_TIME, scene));
}

void GameOverLayer::gotoGameScene() {
	auto scene = GameScene::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(TRAINDITION_TIME, scene));
}

void GameOverLayer::eventButonRetryTouch(cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType type) {
	switch (type) {
	case cocos2d::ui::Widget::TouchEventType::BEGAN:
		break;
	case cocos2d::ui::Widget::TouchEventType::MOVED:
		break;
	case cocos2d::ui::Widget::TouchEventType::ENDED:
		gotoGameScene();
		break;
	case cocos2d::ui::Widget::TouchEventType::CANCELED:
		break;
	default:
		break;
	}
}

void GameOverLayer::eventButtonHomeTouch(cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType type) {
	switch (type) {
	case cocos2d::ui::Widget::TouchEventType::BEGAN:
		break;
	case cocos2d::ui::Widget::TouchEventType::MOVED:
		break;
	case cocos2d::ui::Widget::TouchEventType::ENDED:
		gotoMainMenuScene();
		break;
	case cocos2d::ui::Widget::TouchEventType::CANCELED:
		break;
	default:
		break;
	}
}

void GameOverLayer::setScore(int tempScore) {
	this->score = tempScore;

	auto userDefault = UserDefault::getInstance();
	highScore = userDefault->getIntegerForKey("HIGHSCORE", 0);

	if (score > highScore) {
		highScore = score;
		userDefault->setIntegerForKey("HIGHSCORE", highScore);
	}

	lblHigh->setString(String::createWithFormat("%d", highScore)->getCString());
	lblScore->setString(String::createWithFormat("%d", score)->getCString());
}
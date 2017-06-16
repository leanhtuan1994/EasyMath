#include "GameScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "Definitions.h"
#include "MainMenuScene.h"
#include "Definitions.h"
#include "GameOverLayer.h"



#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#ifdef SDKBOX_ENABLED
#include "PluginAdMob/PluginAdMob.h"
using namespace sdkbox;
#endif
#endif

USING_NS_CC;

using namespace cocostudio::timeline;

Scene* GameScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
	auto layer = GameScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameScene::init()
{

    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    

	rootNode = CSLoader::createNode("GameScene.csb");
	this->addChild(rootNode);

	// Set time default
	timer = TIME_DEFAULT;

	// Get Button and set touch listener
	this->btnRight = (cocos2d::ui::Button *)rootNode->getChildByName("btnRight");
	btnRight->addTouchEventListener(CC_CALLBACK_2(GameScene::touchEventButtonRight, this));

	this->btnWrong = (cocos2d::ui::Button *)rootNode->getChildByName("btnWrong");
	btnWrong->addTouchEventListener(CC_CALLBACK_2(GameScene::touchEventButtonWrong, this));

	// Get Label Score
	this->lblScore = (cocos2d::ui::Text *)rootNode->getChildByName("lblScore");
	// Get timer
	this->lblTime = (cocos2d::ui::Text *)rootNode->getChildByName("lblTime");
	// Get Label Math
	this->lblMath = (cocos2d::ui::Text *)rootNode->getChildByName("lblMath");

	randomCalculation();

	#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		#ifdef SDKBOX_ENABLED	
			sdkbox::PluginAdMob::cache("home");
		#endif
	#endif



	// Update
	this->scheduleUpdate();


    return true;
}

void GameScene::update(float delta){
	timer -= delta;
	lblTime->setString(String::createWithFormat("%.2f", timer)->getCString());

	if (timer < 0.0f){
		timer = 0.0f;
		lblTime->setString(String::createWithFormat("%.2f", timer)->getCString());
		gotoGameOverLayer();
	}

}

void GameScene::touchEventButtonRight(cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType type){
	switch (type) {
	case cocos2d::ui::Widget::TouchEventType::BEGAN:
		break;
	case cocos2d::ui::Widget::TouchEventType::MOVED:
		break;
	case cocos2d::ui::Widget::TouchEventType::ENDED:
		if (result == 1) {
			timer = TIME_DEFAULT - score* 0.09;
			lblScore->setString(String::createWithFormat("%d", ++score)->getCString());
			randomCalculation();
		} else {
			gotoGameOverLayer();
		}

		break;
	case cocos2d::ui::Widget::TouchEventType::CANCELED:
		break;
	default:
		break;
	}
}

void GameScene::touchEventButtonWrong(cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType type){
	switch (type) {
	case cocos2d::ui::Widget::TouchEventType::BEGAN:
		break;
	case cocos2d::ui::Widget::TouchEventType::MOVED:
		break;
	case cocos2d::ui::Widget::TouchEventType::ENDED:
		if (result == 0) {
			timer = TIME_DEFAULT - score * 0.09;
			lblScore->setString(String::createWithFormat("%d", ++score)->getCString());
			randomCalculation();
		} else {
			gotoGameOverLayer();
		}
		break;
	case cocos2d::ui::Widget::TouchEventType::CANCELED:
		break;
	default:
		break;
	}
}


void GameScene::randomCalculation() {

	randomMath();

	switch (math) {
	case SUMMATION:
		randomSummation();
		break;
	case SUBTRACTION:
		randomSubtraction();
		break;
	case DIVISION:
		randomDivision();
		break;
	case MULTIPLICATION:
		randomMultiplication();
		break;
	default:
		break;
	}
}

void GameScene::randomMath() {
	int rand = random(0, 3);
	switch (rand) {
	case 0:
		math = SUMMATION;
		break;
	case 1:
		math = SUBTRACTION;
		break;
	case 2:
		math = DIVISION;
		break;
	case 3:
		math = MULTIPLICATION;
		break;
	default:
		break;
	}

}

void GameScene::randomSummation() {
	int firstNum = random(-10 - score, score + 10);
	int secondNum = random(score, score + 15);
	int thirdNum;

	result = random(0, 1);

	// If result = true
	if (result == 1) {
		thirdNum = firstNum + secondNum;
	} else {
		int a = firstNum, b = secondNum;
		if (a > b) {
			int temp = a;
			a = b;
			b = temp;
		}

		do {
			b = a + b * 2;
			if (a > b) { 
				int temp = a;
				a = b;
				b = temp;
			}
			thirdNum = random(a, b);
		} while (thirdNum == (firstNum + secondNum));

	}

	mathStr = String::createWithFormat("%d + %d = %d", firstNum, secondNum, thirdNum)->getCString();
	lblMath->setString(mathStr);
}

void GameScene::randomDivision() {
	int firstNum;
	int secondNum = random(2, 9);
	int thirdNum;

	result = random(0, 1);

	// If result = true
	if (result == 1) {
		do {
			thirdNum = random(-score, 10 + score);
		} while (thirdNum == 0);
		firstNum = secondNum * thirdNum;
	} else {
		thirdNum = random(-score, 10 + score);
		do {
			int a = secondNum, b = thirdNum*secondNum;
			if (a > b) {
				int temp = a;
				a = b;
				b = temp;
			}
			firstNum = random(a, b);
		} while (firstNum == (secondNum * thirdNum));
	}

	mathStr = String::createWithFormat("%d / %d = %d", firstNum, secondNum, thirdNum)->getCString();
	lblMath->setString(mathStr);
}

void GameScene::randomMultiplication() {
	int firstNum = random(score, score + 10);
	int secondNum = random(2, 9 + score);
	int thirdNum;

	result = random(0, 1);

	// If result = true
	if (result == 1) {
		thirdNum = secondNum * firstNum;
	} else {
		do{
			thirdNum = random(firstNum*secondNum - firstNum, firstNum*secondNum + secondNum);
		} while (thirdNum == (secondNum * firstNum));
	}

	mathStr = String::createWithFormat("%d x %d = %d", firstNum, secondNum, thirdNum)->getCString();
	lblMath->setString(mathStr);
}


void GameScene::randomSubtraction() {
	int firstNum = random(-10 - score, score + 10);
	int secondNum = random(score, score + 15);
	int thirdNum;

	result = random(0, 1);

	// If result = true
	if (result == 1) {
		thirdNum = firstNum - secondNum;
	} else {
		int a = firstNum, b = secondNum;
		if (a < b) {
			int temp = a;
			a = b;
			b = temp;
		}

		do {
			thirdNum = random( b , a);
		} while (thirdNum == (firstNum - secondNum));

	}

	mathStr = String::createWithFormat("%d - %d = %d", firstNum, secondNum, thirdNum)->getCString();
	lblMath->setString(mathStr);
}

void GameScene::gotoGameOverLayer() {
	
	this->pause();
	btnRight->setEnabled(false);
	btnWrong->setEnabled(false);
	

	auto gameOverLayer = GameOverLayer::create();
	gameOverLayer->setPosition(origin.x, origin.y);
	gameOverLayer->setScore(score);
	this->addChild(gameOverLayer);
}


#include "MainMenuScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "GameScene.h"
#include "Definitions.h"

USING_NS_CC;

using namespace cocostudio::timeline;

Scene* MainMenuScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
	auto layer = MainMenuScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MainMenuScene::init()
{

    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

   
	auto rootNode = CSLoader::createNode("MainMenuScene.csb");
	addChild(rootNode);


	btnPlay = (cocos2d::ui::Button *) rootNode->getChildByName("btn_mainmenu_play");
	btnPlay->addTouchEventListener(CC_CALLBACK_2(MainMenuScene::touchEvent, this));


    return true;
}


void MainMenuScene::touchEvent(cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType type){
	switch (type){
	case cocos2d::ui::Widget::TouchEventType::ENDED:
		gotoGameMenuScene(TRAINDITION_TIME);
		break;
	default:
		break;
	}
}

void MainMenuScene::gotoGameMenuScene(float dt){
	auto scene = GameScene::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(TRAINDITION_TIME, scene));
}
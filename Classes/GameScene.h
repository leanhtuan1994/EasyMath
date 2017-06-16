#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"


enum MATH {
	SUMMATION,
	SUBTRACTION,
	DIVISION, 
	MULTIPLICATION
};

class GameScene : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

    // implement the "static create()" method manually
	CREATE_FUNC(GameScene);

	void touchEventButtonRight(cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType type);
	void touchEventButtonWrong(cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType type);
	
	void randomMath();
	void randomCalculation();
	void randomSummation();
	void randomSubtraction();
	void randomDivision();
	void randomMultiplication();

	void update(float delta);

	void gotoGameOverLayer();

private:
	cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
	cocos2d::Vec2 origin = cocos2d::Director::getInstance()->getVisibleOrigin();


	cocos2d::Node			*rootNode;
	cocos2d::ui::Button		*btnRight;
	cocos2d::ui::Button		*btnWrong;
	cocos2d::ui::Text		*lblTime;
	cocos2d::ui::Text		*lblScore;
	cocos2d::ui::Text		*lblMath;
	
	MATH					math;
	int						score = 0;
	float					timer;
	std::string				mathStr;
	bool					result;



};

#endif // __GAME_SCENE_H__

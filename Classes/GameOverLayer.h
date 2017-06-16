#ifndef __GAME_OVER_SCENE_H__
#define __GAME_OVER_SCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

class GameOverLayer : public cocos2d::Layer
{
public:

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	// implement the "static create()" method manually
	CREATE_FUNC(GameOverLayer);

	void gotoGameScene();
	void gotoMainMenuScene();

	void setScore(int tempScore);


private:
	cocos2d::ui::Button		*btnGoHome;
	cocos2d::ui::Button		*btnRetry;
	cocos2d::ui::Text		*lblScore;
	cocos2d::ui::Text		*lblHigh;

	int score;
	int highScore;


	void eventButonRetryTouch(cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType type);
	void eventButtonHomeTouch(cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType type);


};

#endif // __GAME_OVER_SCENE_H__

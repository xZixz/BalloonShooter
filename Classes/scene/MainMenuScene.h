/*
 * MainMenuScene.h
 *
 *  Created on: Sep 6, 2014
 *      Author: dudu
 */

#ifndef MAINMENUSCENE_H_
#define MAINMENUSCENE_H_

#include "cocos2d.h"

USING_NS_CC;

class MainMenuScene : public Layer {
public:

	static Scene* createScene();
	bool virtual init();

	virtual void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* unusedEvent);

	void menuCallback(Ref*);

	MainMenuScene();
	virtual ~MainMenuScene();

	CREATE_FUNC(MainMenuScene);

};

#endif /* MAINMENUSCENE_H_ */

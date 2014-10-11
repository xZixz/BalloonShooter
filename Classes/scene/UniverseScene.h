/*
 * UniverseScene.h
 *
 *  Created on: Sep 25, 2014
 *      Author: dudu
 */

#ifndef UNIVERSESCENE_H_
#define UNIVERSESCENE_H_

#include "cocos2d.h"

USING_NS_CC;

class UniverseScene : public Layer {
public:

	static Scene* createScene();
	CREATE_FUNC(UniverseScene);
	virtual bool init();
	void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* unusedEvent);

	virtual void btnCallback(Ref*);

	UniverseScene();
	virtual ~UniverseScene();
};

#endif /* UNIVERSESCENE_H_ */

/*
 * StageChooserScene.h
 *
 *  Created on: Sep 29, 2014
 *      Author: dudu
 */

#ifndef STAGECHOOSERSCENE_H_
#define STAGECHOOSERSCENE_H_

#include "cocos2d.h"

USING_NS_CC;

class StageChooserScene : public Layer {
public:

	static Scene* createScene(const std::string& planet_name);
	static StageChooserScene* create(const std::string& planet_name);
	virtual bool init(const std::string& planet_name);

	virtual void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* unusedEvent);

	StageChooserScene();
	virtual ~StageChooserScene();

	virtual void stageBtnCallback(Ref*);

protected:
	std::string planet_name_;
};

#endif /* STAGECHOOSERSCENE_H_ */

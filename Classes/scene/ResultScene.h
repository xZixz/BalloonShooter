/*
 * ResultScene.h
 *
 *  Created on: Sep 25, 2014
 *      Author: dudu
 */


#ifndef RESULTSCENE_H_
#define RESULTSCENE_H_

#include "cocos2d.h"
#include "../manager/StageManager.h"

USING_NS_CC;

class ResultScene : public Layer {
public:

	static Scene* createScene(bool is_win, int score, int star_num, Stage current_stage);
	static ResultScene* create(bool is_win, int score, int star_num, Stage current_stage);
	virtual bool init(bool is_win, int score, int star_num, Stage current_stage);

	virtual void btnCallback(Ref*);

	ResultScene();
	virtual ~ResultScene();
protected:
	bool is_win_;
	int score_;
	int star_num_;
	Stage current_stage_;
};

#endif /* RESULTSCENE_H_ */

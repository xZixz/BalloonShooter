/*
 * ResultScene.h
 *
 *  Created on: Sep 25, 2014
 *      Author: dudu
 */

#include "cocos2d.h"

USING_NS_CC;

#ifndef RESULTSCENE_H_
#define RESULTSCENE_H_

class ResultScene : public Layer {
public:

	static Scene* createScene(bool is_win, int score, int star_num);
	static ResultScene* create(bool is_win, int score, int star_num);
	virtual bool init(bool is_win, int score, int star_num);

	virtual void btnCallback(Ref*);

	ResultScene();
	virtual ~ResultScene();
protected:
	bool is_win_;
	int score_;
	int star_num_;
};

#endif /* RESULTSCENE_H_ */

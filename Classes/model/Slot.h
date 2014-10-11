/*
 * Slot.h
 *
 *  Created on: Sep 11, 2014
 *      Author: dudu
 */

#ifndef SLOT_H_
#define SLOT_H_

#include "cocos2d.h"

class Ball;

USING_NS_CC;

class Slot : public Ref {
public:

	static Slot* create(Ball*, Vec2);
	virtual bool init(Ball*, Vec2);

	Slot();
	virtual ~Slot();
	Ball* ball_;
	Vec2 pos_;
	int row_index_;
	int column_index_;
	bool is_traversed_;
};

#endif /* SLOT_H_ */

/*
 * Slot.cpp
 *
 *  Created on: Sep 11, 2014
 *      Author: dudu
 */

#include "Slot.h"

Slot* Slot::create(Ball* ball, Vec2 pos){
	Slot* slot = new (std::nothrow) Slot();
	if (slot && slot->init(ball,pos)){
		slot->autorelease();
		return slot;
	}
	CC_SAFE_DELETE(slot);
	return nullptr;
}

bool Slot::init(Ball* ball, Vec2 pos){
	ball_ = ball;
	pos_ = pos;
	return true;
}

Slot::Slot():
ball_(nullptr),
pos_(Vec2::ZERO),
is_traversed_(false),
row_index_(0),
column_index_(0)
{
}

Slot::~Slot() {
}


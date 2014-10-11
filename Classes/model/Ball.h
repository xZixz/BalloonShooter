/*
 * Ball.h
 *
 *  Created on: Sep 10, 2014
 *      Author: dudu
 */

#ifndef BALL_H_
#define BALL_H_

#include "cocos2d.h"
#include "../delegate/BallDelegate.h"
#include "Slot.h"

USING_NS_CC;

class Ball : public Sprite {
public:

	static Ball* create(const std::string& ballname);
	bool virtual init(const std::string& ballname);

	void shot(Vec2 ref_point);
	void flyTo(Vec2 ref_point);
	void doneShot();
	void recordPos(float dt);
	void bounceVertical();

	void installIntoSlot(Slot* slot);

	Ball();
	virtual ~Ball();

	bool isBouncing(){
		return is_bouncing_;
	}

	void set_is_bouncing(bool val){
		is_bouncing_ = val;
	}

	void setSpawnPos(Vec2 pos){
		spawn_pos_ = pos;
	}

	void setGameScene(BallDelegate* gamescene){
		this->gamescene_ = gamescene;
	}

	void setSlot(Slot* slot){
		slot_ = slot;
	}

	Slot* getSlot(){
		return slot_;
	}

	std::string getName(){
		return name_;
	}

protected:
	std::string name_;
	Vec2 spawn_pos_;
	BallDelegate* gamescene_;
	Slot* slot_;

//	Ball* neighborball_1_;
//	Ball* neighborball_2_;
//	Ball* neighborball_3_;
//	Ball* neighborball_4_;
//	Ball* neighborball_5_;
//	Ball* neighborball_6_;

	Vec2 pre_pos_;
	Vec2 cur_pos_;
	bool is_bouncing_;

};

#endif /* BALL_H_ */

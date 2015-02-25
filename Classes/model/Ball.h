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
#include "../scene/GameScene.h"

USING_NS_CC;

class GameScene;

class Ball : public Sprite {
public:

	enum SpecialType {
		SPECIAL_0 = 0x0,
		SPECIAL_1 = 0x1,
		SPECIAL_2 = 0x10,
		SPECIAL_3 = 0x100,
		SPECIAL_4 = 0x1000,
		//--- special combo 2
		SPECIAL_1_2 = SPECIAL_1 | SPECIAL_2,
		SPECIAL_1_3 = SPECIAL_1 | SPECIAL_3,
		SPECIAL_1_4 = SPECIAL_1 | SPECIAL_4,
		SPECIAL_2_3 = SPECIAL_2 | SPECIAL_3,
		SPECIAL_2_4 = SPECIAL_2 | SPECIAL_4,
		SPECIAL_3_4 = SPECIAL_3 | SPECIAL_4,
		//--- special combo 3
		// Reserved
	};

	static Ball* create(const std::string& ballname);
	bool virtual init(const std::string& ballname);

	void shot(Vec2 ref_point);
	void flyTo(Vec2 ref_point);
	void doneShot();
	void recordPos(float dt);
	void bounceVertical();
	void explode();
	void dropFade();

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

	void setGameScene(GameScene* gamescene){
		this->g_scene_ = gamescene;
	}

	GameScene* getGameScene(){
		return g_scene_;
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

	void addSpecialType(SpecialType type){
		special_type_ = special_type_ | type;
	}

	void removeSpecialType(SpecialType type){
		special_type_ =  special_type_ & (~type) ;
	}

	bool containSpecialType(SpecialType type){
		return (special_type_ & type);
	}

	int getSpecialType(){
		return special_type_;
	}

	// Fire ball
	virtual void destroyABall();
	virtual void endFire(float time);
	virtual void setBoomingTime(float time);

protected:
	std::string name_;
	Vec2 spawn_pos_;
	BallDelegate* gamescene_;
	GameScene* g_scene_;
	Slot* slot_;
	int special_type_;

	Vec2 pre_pos_;
	Vec2 cur_pos_;
	bool is_bouncing_;

	float score_;
	float velocity_;

	bool booming_;
	float booming_time_;

};

#endif /* BALL_H_ */

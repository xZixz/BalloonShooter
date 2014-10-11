/*
 * Ball.cpp
 *
 *  Created on: Sep 10, 2014
 *      Author: dudu
 */

#include "Ball.h"
#include "../GameMacros.h"

Ball* Ball::create(const std::string& ballname){
	Ball* ball = new (std::nothrow) Ball();
	if (ball && ball->init(ballname)){
		ball->autorelease();
		return ball;
	}
	CC_SAFE_DELETE(ball);
	return nullptr;
}

bool Ball::init(const std::string& ballname){
	name_ = ballname;
	std::string filename = name_ + std::string("_ball.png");
	if (Sprite::initWithFile(filename)){
		return true;
	}
	return false;
}

void Ball::shot(Vec2 ref_point){

	flyTo(ref_point);

	pre_pos_ = getPosition();
	cur_pos_ = pre_pos_;
	schedule(schedule_selector(Ball::recordPos));

}

void Ball::recordPos(float dt){
	pre_pos_ = cur_pos_;
	cur_pos_ = getPosition();
}

void Ball::flyTo(Vec2 ref_point){
	Vec2 current_pos = getPosition();
	Vec2 des_pos;
	des_pos.y = Director::getInstance()->getWinSize().height;
	des_pos.x = ((des_pos.y - current_pos.y)/(ref_point.y - current_pos.y))*(ref_point.x - current_pos.x) + current_pos.x;
	float distance = DISTANCE_BETWEEN(current_pos,des_pos);
	float velocity = 1500;
	float time = distance/velocity;
	runAction(Sequence::create(MoveTo::create(time,des_pos),CallFunc::create(this,callfunc_selector(Ball::doneShot)),NULL));
}

void Ball::bounceVertical(){
	is_bouncing_ = true;
	recordPos(0);
	stopAllActions();
	Vec2 ref_pos = Vec2(pre_pos_.x,cur_pos_.y*2 - pre_pos_.y);
	flyTo(ref_pos);
}

void Ball::doneShot(){
	stopAllActions();
	gamescene_->ballDoneShot(this);
}

void Ball::installIntoSlot(Slot* slot){
	setPosition(slot->pos_);
	slot_ = slot;
	slot_->ball_ = this;
}

Ball::Ball():
gamescene_(nullptr),
slot_(nullptr),
//neighborball_1_(nullptr),
//neighborball_2_(nullptr),
//neighborball_3_(nullptr),
//neighborball_4_(nullptr),
//neighborball_5_(nullptr),
//neighborball_6_(nullptr),
is_bouncing_(false)
{
	// TODO Auto-generated constructor stub

}

Ball::~Ball() {
	// TODO Auto-generated destructor stub
}


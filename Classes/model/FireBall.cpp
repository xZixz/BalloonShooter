/*
 * FireBall.cpp
 *
 *  Created on: Jan 14, 2015
 *      Author: dudu
 */

#include "FireBall.h"

#define FIRE_BALL_NAME "green"

FireBall* FireBall::create(){
	FireBall* fire_ball = new FireBall();
	if (fire_ball && fire_ball->init()){
		fire_ball->autorelease();
		return fire_ball;
	}
	CC_SAFE_DELETE(fire_ball);
	return nullptr;
}

FireBall* FireBall::create(Ball* ball){
	FireBall* fire_ball = new FireBall();
	if (fire_ball && fire_ball->init(ball)){
		fire_ball->autorelease();
		return fire_ball;
	}
	CC_SAFE_DELETE(fire_ball);
	return nullptr;
}

bool FireBall::init(){
	if (Ball::init(FIRE_BALL_NAME)){
		addSpecialType(Ball::SpecialType::SPECIAL_4);
		return true;
	}
	return false;
}

bool FireBall::init(Ball* ball){
	if (Ball::init(ball->getName())){
		addSpecialType(Ball::SpecialType::SPECIAL_4);
		return true;
	}
	return false;
}

void FireBall::destroyABall(){
//	ball_destroy_num_--;
//	if (ball_destroy_num_ == 0){
//		doneShot();
//	}
	if (!booming_){
		booming_ = true;
		scheduleOnce(schedule_selector(FireBall::endFire),booming_time_);
	}
}

void FireBall::setBoomingTime(float time){
	booming_time_ = time;
}

void FireBall::endFire(float time){
	// TODO
	removeSpecialType(Ball::SpecialType::SPECIAL_4) ; // remove fire ball type
	if (special_type_ == Ball::SpecialType::SPECIAL_0) { // if there is not any other type, done-shot
		doneShot();
	}
}

void FireBall::setMaxBallDestroy(int max){
	ball_destroy_num_ = max;
}

FireBall::FireBall():
ball_destroy_num_(4),
booming_(false),
booming_time_(0.2f)
{
}

FireBall::~FireBall() {
}


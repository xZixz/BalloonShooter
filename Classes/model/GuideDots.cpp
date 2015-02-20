/*
 * GuideDots.cpp
 *
 *  Created on: Nov 6, 2014
 *      Author: dudu
 */

#include "GuideDots.h"

GuideDots* GuideDots::createWithFileName(const std::string& file_name){
	GuideDots* guide_dots = new GuideDots();
	if (guide_dots && guide_dots->initWithFileName(file_name)){
		guide_dots->autorelease();
		return guide_dots;
	}
	CC_SAFE_DELETE(guide_dots);
	return nullptr;
}

bool GuideDots::initWithFileName(const std::string& file_name){
	if (Node::init()){
		init();
		initDots(file_name);
		return true;
	}
	return false;
}

void GuideDots::initDots(const std::string& file_name){
		for ( int i = 0; i < num_of_dots_; i++){
			Sprite* a_dot = Sprite::create(file_name);
			Vec2 dot_pos = Vec2(0,i*(space_length_ + a_dot->getContentSize().height));
			a_dot->setPosition(dot_pos);
			addChild(a_dot);
			dots_.pushBack(a_dot);
		}
}

void GuideDots::setDeg(Touch* touch){
	Vec2 touchPos = touch->getLocation();
	float delta_y = touchPos.y - getPosition().y;
	float delta_x = touchPos.x - getPosition().x;

	float tangent = delta_y/delta_x;
	float degree = CC_RADIANS_TO_DEGREES(atan(tangent));
	if (delta_x < 0) degree += 180;
	log("Deg: %f",degree);
	setDeg(degree);
}

void GuideDots::guide(){
	for ( int i = 0; i < num_of_dots_; i++){
		Sprite* a_dot = (Sprite*)dots_.at(i);
		Vec2 dot_pos;
		dot_pos.x = i*(space_length_ + a_dot->getContentSize().width)*cos(CC_DEGREES_TO_RADIANS(deg_));
		dot_pos.y = i*(space_length_ + a_dot->getContentSize().width)*sin(CC_DEGREES_TO_RADIANS(deg_));
		if (dot_pos.x > side_bound_){
			dot_pos.x = 2*side_bound_ - dot_pos.x;
		} else if (dot_pos.x < -side_bound_){
			dot_pos.x = 2*(-side_bound_) - dot_pos.x;
		}
		a_dot->setPosition(dot_pos);
	}
}

void GuideDots::setDeg(float deg){
	deg_ = deg;
	guide();
}

bool GuideDots::init(){
	num_of_dots_ = 20;
	space_length_ = 20;
	deg_ = 0;

	return true;
}

GuideDots::GuideDots():
num_of_dots_(0),
space_length_(0),
deg_(0),
side_bound_(0)
{
}

GuideDots::~GuideDots() {
}


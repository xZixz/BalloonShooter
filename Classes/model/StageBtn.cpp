/*
 * StageBtn.cpp
 *
 *  Created on: Oct 4, 2014
 *      Author: dudu
 */

#include "StageBtn.h"

StageBtn* StageBtn::create(const std::string& planet_name, const ccMenuCallback& callback, int star_num){
	StageBtn* btn = new StageBtn();
	if (btn && btn->init(planet_name,callback,star_num)){
		btn->autorelease();
		return btn;
	}
	CC_SAFE_DELETE(btn);
	return nullptr;
}

bool StageBtn::init(const std::string& planet_name, const ccMenuCallback& callback, int star_num){
	std::string stage_file = planet_name + ".png";
	std::string stage_file_disable = planet_name + "_disable.png";
	if(MenuItemImage::initWithNormalImage(stage_file,stage_file,stage_file_disable,callback)){
		star_num_ = star_num;
		char tmp_char[10];
		sprintf(tmp_char,"%s_%d.png","star",star_num_);
		Sprite* star_sprite = Sprite::create(tmp_char);
		star_sprite->setPosition(getContentSize()/2);
		addChild(star_sprite);
		return true;
	}
	return false;
}

StageBtn::StageBtn() {
}

StageBtn::~StageBtn() {
}


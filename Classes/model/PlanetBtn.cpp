/*
 * PlanetBtn.cpp
 *
 *  Created on: Sep 27, 2014
 *      Author: dudu
 */

#include "PlanetBtn.h"
#include "../database/PlanetInfo.h"

#define LOCK_ZORDER 1

PlanetBtn* PlanetBtn::create(Node* normalSprite, Node* selectedSprite, const ccMenuCallback& callback){
	PlanetBtn* planet_btn = new PlanetBtn();
	if (planet_btn && planet_btn->initWithNormalSprite(normalSprite,selectedSprite,nullptr,callback)){
		planet_btn->autorelease();
		planet_btn->selfInit();
		return planet_btn;
	}
	CC_SAFE_DELETE(planet_btn);
	return nullptr;
}

void PlanetBtn::selfInit(){
	lock_sprite_ = Sprite::createWithSpriteFrameName("planet_locked.png");
	lock_sprite_->setPosition(getContentSize()/2);
	lock_sprite_->setVisible(false);
	addChild(lock_sprite_,LOCK_ZORDER);
}

void PlanetBtn::setLocked(){
	setEnabled(false);
	lock_sprite_->setVisible(true);
}

PlanetBtn::PlanetBtn():
lock_sprite_(nullptr)
{
}

PlanetBtn::~PlanetBtn() {
}


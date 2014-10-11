/*
 * GrowButton.cpp
 *
 *  Created on: Sep 6, 2014
 *      Author: dudu
 */

#include "GrowButton.h"

GrowButton* GrowButton::create(const std::string& fileName,  const ccMenuCallback& callback){
	GrowButton* button = new (std::nothrow) GrowButton();
	if (button && button->init(fileName,callback)){
		button->autorelease();
		return button;
	}
	CC_SAFE_DELETE(button);
	return nullptr;
}

bool GrowButton::init(const std::string& fileName,  const ccMenuCallback& callback){
	if (MenuItemImage::initWithNormalImage(fileName,fileName,"",callback)){
		return true;
	}
	return false;
}

void GrowButton::selected(){
	setScale(_scaleRatio);
	MenuItemImage::selected();
}

void GrowButton::unselected(){
	setScale(1.0f);
	MenuItemImage::unselected();
}

GrowButton::GrowButton():
_scaleRatio(1.2f)
{
	// TODO Auto-generated constructor stub

}

GrowButton::~GrowButton() {
	// TODO Auto-generated destructor stub
}


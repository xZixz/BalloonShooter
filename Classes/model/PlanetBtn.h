/*
 * PlanetBtn.h
 *
 *  Created on: Sep 27, 2014
 *      Author: dudu
 */

#ifndef PLANETBTN_H_
#define PLANETBTN_H_

#include "cocos2d.h"

USING_NS_CC;

class PlanetBtn : public MenuItemSprite {
public:

	static PlanetBtn* create(Node* normalSprite, Node* selectedSprite, const ccMenuCallback& callback);
	virtual void selfInit();
	virtual void setLocked();

	PlanetBtn();
	virtual ~PlanetBtn();
protected:
	Sprite* lock_sprite_;
};

#endif /* PLANETBTN_H_ */

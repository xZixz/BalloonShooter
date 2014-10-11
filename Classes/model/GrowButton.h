/*
 * GrowButton.h
 *
 *  Created on: Sep 6, 2014
 *      Author: dudu
 */

#ifndef GROWBUTTON_H_
#define GROWBUTTON_H_

#include "cocos2d.h"

USING_NS_CC;

class GrowButton : public MenuItemImage {
public:

	static GrowButton* create(const std::string&,  const ccMenuCallback& callback);
	virtual bool init(const std::string&,  const ccMenuCallback& callback);

	virtual void selected();
	virtual void unselected();

	GrowButton();
	virtual ~GrowButton();
private:
	float _scaleRatio;
};

#endif /* GROWBUTTON_H_ */

/*
 * StageBtn.h
 *
 *  Created on: Oct 4, 2014
 *      Author: dudu
 */

#ifndef STAGEBTN_H_
#define STAGEBTN_H_

#include "cocos2d.h"

USING_NS_CC;

class StageBtn : public MenuItemImage {
public:

	static StageBtn* create(const std::string& planet_name, const ccMenuCallback& callback, int star_num);
	virtual bool init(const std::string& planet_name, const ccMenuCallback& callback, int star_num);

	StageBtn();
	virtual ~StageBtn();
protected:
	int star_num_;
};

#endif /* STAGEBTN_H_ */

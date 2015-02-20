/*
 * GuideDots.h
 *
 *  Created on: Nov 6, 2014
 *      Author: dudu
 */

#ifndef MODEL_GUIDEDOTS_H_
#define MODEL_GUIDEDOTS_H_

#include "cocos2d.h"

USING_NS_CC;

class GuideDots : public Node {
public:

	static GuideDots* createWithFileName(const std::string& file_name);
	virtual bool initWithFileName(const std::string& file_name);
	virtual bool init();
	virtual void initDots(const std::string& file_name);
	virtual void setDeg(float deg);
	virtual void setDeg(Touch* touch);
	virtual void guide();

	virtual void setSideBound(float value){
		side_bound_ = value;
	}

	GuideDots();
	virtual ~GuideDots();
private:
	std::string file_name_;
	Vector<Sprite*> dots_;
	int num_of_dots_;
	float space_length_;
	float deg_;
	float side_bound_;
};

#endif /* MODEL_GUIDEDOTS_H_ */

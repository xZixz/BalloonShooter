/*
 * FireBall.h
 *
 *  Created on: Jan 14, 2015
 *      Author: dudu
 */

#ifndef MODEL_FIREBALL_H_
#define MODEL_FIREBALL_H_

#include "Ball.h"

class FireBall : public Ball {
public:

	static FireBall* create();
	virtual bool init();

	FireBall();
	virtual ~FireBall();

	virtual void destroyABall();
	virtual void endFire(float time);
	virtual void setMaxBallDestroy(int max);
	virtual void setBoomingTime(float time);

protected:
	int ball_destroy_num_;
	bool booming_;
	float booming_time_;
};

#endif /* MODEL_FIREBALL_H_ */

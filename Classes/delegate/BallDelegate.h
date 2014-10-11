/*
 * BallDelegate.h
 *
 *  Created on: Sep 10, 2014
 *      Author: dudu
 */

#ifndef BALLDELEGATE_H_
#define BALLDELEGATE_H_

class Ball;

class BallDelegate {
public:
	virtual void ballDoneShot(Ball* ) = 0;
	virtual ~BallDelegate(){};
};



#endif /* BALLDELEGATE_H_ */

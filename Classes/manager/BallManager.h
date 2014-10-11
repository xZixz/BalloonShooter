/*
 * BallManager.h
 *
 *  Created on: Sep 10, 2014
 *      Author: dudu
 */

#ifndef BALLMANAGER_H_
#define BALLMANAGER_H_

#define GREEN_BALL_NAME "green"
#define BLACK_BALL_NAME "black"
#define BLUE_BALL_NAME "blue"
#define CYAN_BALL_NAME "cyan"
#define ORANGE_BALL_NAME "orange"
#define PURPLE_BALL_NAME "purple"
#define RED_BALL_NAME "red"
#define YELLOW_BALL_NAME "yellow"
#define NULL_BALL_NAME "n0"

#include "cocos2d.h"

USING_NS_CC;

class BallManager : public Ref {
public:

	static BallManager* getInstance();
	virtual void selfInit();
	std::vector<std::string> get_available_ball_list_by_stage_index(int index);

	BallManager();
	virtual ~BallManager();
protected:
	std::vector<std::vector<std::string>> available_ball_stage_list_;
};

#endif /* BALLMANAGER_H_ */

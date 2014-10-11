/*
 * BallManager.cpp
 *
 *  Created on: Sep 10, 2014
 *      Author: dudu
 */

#include "BallManager.h"

static BallManager* theInstance = NULL;

BallManager* BallManager::getInstance(){
	if (!theInstance){
		theInstance = new (std::nothrow)BallManager();
		theInstance->autorelease();
		theInstance->retain();
		theInstance->selfInit();
	}
	return theInstance;
}

void BallManager::selfInit(){
	std::vector<std::string> balls_stage_1;
	balls_stage_1.push_back(GREEN_BALL_NAME);
	balls_stage_1.push_back(RED_BALL_NAME);
	available_ball_stage_list_.push_back(balls_stage_1);
}

std::vector<std::string> BallManager::get_available_ball_list_by_stage_index(int index){
	return (std::vector<std::string>)available_ball_stage_list_.at(index-1);
}

BallManager::BallManager() {
	// TODO Auto-generated constructor stub

}

BallManager::~BallManager() {
	// TODO Auto-generated destructor stub
}


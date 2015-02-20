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
	initialize_unshotable_ball_list();
}

void BallManager::initialize_unshotable_ball_list(){
	unshotable_ball_list_.push_back(KEY_BALL_NAME);
}

bool BallManager::isUnshotable(std::string ball_name){
	for (std::string unshotable_ball_name : unshotable_ball_list_){
		if (!unshotable_ball_name.compare(ball_name)){
			return true;
		}
	}
	return false;
}

std::vector<std::string> BallManager::getUnshotableBallList(){
	return unshotable_ball_list_;
}

BallManager::BallManager() {
	// TODO Auto-generated constructor stub

}

BallManager::~BallManager() {
	// TODO Auto-generated destructor stub
}


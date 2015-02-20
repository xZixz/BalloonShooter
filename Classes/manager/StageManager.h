/*
 * StageManager.h
 *
 *  Created on: Sep 22, 2014
 *      Author: dudu
 */

#ifndef STAGEMANAGER_H_
#define STAGEMANAGER_H_

#define GREEN 	GREEN_BALL_NAME
#define BLACK 	BLACK_BALL_NAME
#define BLUE 	BLUE_BALL_NAME
#define CYAN 	CYAN_BALL_NAME
#define ORANGE 	ORANGE_BALL_NAME
#define PURPLE 	PURPLE_BALL_NAME
#define RED 	RED_BALL_NAME
#define YELLOW 	YELLOW_BALL_NAME
#define N0 	NULL_BALL_NAME
#define KEY KEY_BALL_NAME

#include "cocos2d.h"
#include "../database/PlanetInfo.h"
#include "../database/StageInfo.h"
#include "BallManager.h"

USING_NS_CC;

typedef std::vector<std::vector<std::string>> BallsSetup;

struct Stage {
	std::string planet_name_;
	int no_;
};

struct ScoreStarSet {
	int star_3;
	int star_2;
};

struct StageSetup {
	int star_3;
	int star_2;
	float time_limit;
	int ball_limit;
};

class StageManager : public Ref {
public:

	static StageManager* getInstance();
	virtual void selfInit();
	virtual void initializeBallsSetupList();
	virtual void initializeBallsSetupMap();
	virtual void initializeScoreStarSetMap();
	virtual void initializeStageSetupMap();
	virtual void initPlanetNameList();
	virtual void initPlanetInfoList();
	virtual void initStageInfoList();

	virtual BallsSetup getBallsSetupByStage(int index);
	virtual BallsSetup getBallsSetupByStage(Stage stage);
	virtual BallsSetup getBallsSetupByStageJSON(Stage stage);
	virtual PlanetInfo* getPlanetInfoByName(const std::string& name);
	virtual std::vector<StageInfo*> getStageInfosByName(const std::string& name);
	StageInfo* getStageInfoByStage(Stage stage);
	virtual ScoreStarSet getScoreStarSetByStage(Stage stage);
	virtual StageSetup getStageSetupByStage(Stage stage);
	std::string getNextPlanetName(std::string);

	StageManager();
	virtual ~StageManager();

	virtual void addNewStageInfoList(StageInfo* stage_info);

protected:
	std::vector<BallsSetup> balls_setup_list_;
	std::map<std::string,std::vector<BallsSetup>> balls_setup_map_;
	std::map<std::string,std::vector<ScoreStarSet>> score_star_map_;
	std::map<std::string,std::vector<StageSetup>> stage_setup_map_;
	std::vector<PlanetInfo*> planet_info_list_;
	std::vector<StageInfo*> stage_info_list_;
	std::vector<std::string> planet_name_list_;
};

#endif /* STAGEMANAGER_H_ */

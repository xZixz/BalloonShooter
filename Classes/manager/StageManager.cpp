/*
 * StageManager.cpp
 *
 *  Created on: Sep 22, 2014
 *      Author: dudu
 */

#include "StageManager.h"
#include "../database/parser/PlanetInfoParser.h"
#include "../database/parser/StageInfoParser.h"
#include "../sqlite/SqliteUtil.h"
#include "../GameConstants.h"

static StageManager* theInstance = NULL;

StageManager* StageManager::getInstance(){
	if (!theInstance){
		theInstance = new StageManager();
		theInstance->autorelease();
		theInstance->retain();
		theInstance->selfInit();
	}
	return theInstance;
}

void StageManager::selfInit(){
	initPlanetInfoList();
	initStageInfoList();
//	initializeBallsSetupList();
	initializeBallsSetupMap();
}

void StageManager::initializeBallsSetupList(){
//	balls_setup_list_.push_back(stage_1);
}

void StageManager::initializeBallsSetupMap(){
	std::vector<BallsSetup> moon_balls_setup;
	BallsSetup stage_1;
	std::vector<std::string> row_1 = {N0, GREEN, GREEN, GREEN, GREEN, GREEN, N0, N0, N0, N0};
	std::vector<std::string> row_2 = {N0, GREEN, GREEN, GREEN, GREEN, GREEN, N0, N0, N0};
	std::vector<std::string> row_3 = {N0, RED, RED, RED, RED, RED, N0, N0, N0, N0};
	std::vector<std::string> row_4 = {N0, RED, RED, RED, RED, RED, N0, N0, N0};
	stage_1 = {row_1,row_2,row_3,row_4};
	moon_balls_setup.push_back(stage_1);

	balls_setup_map_.insert(std::pair<std::string,std::vector<BallsSetup>>(MOON_NAME,moon_balls_setup));
}

void StageManager::initPlanetInfoList(){
	executeNonQuery(PlanetInfo::getCreateQuery());
	Ref* itor;
	PlanetInfoParser parser;
	__Array* arr = executeGetMultiRecord(PlanetInfo::getSelectQuery(),parser);
	CCARRAY_FOREACH(arr,itor){
		PlanetInfo* planet_info = (PlanetInfo*)itor;
		planet_info_list_.push_back(planet_info);
	}
	arr->removeAllObjects();
	if (planet_info_list_.size() == 0){
		PlanetInfo* moon_info = PlanetInfo::create(MOON_NAME,1);
		moon_info->insertPlanetInfo();
		planet_info_list_.push_back(moon_info);
		PlanetInfo* venus_info = PlanetInfo::create(VENUS_NAME,0);
		venus_info->insertPlanetInfo();
		planet_info_list_.push_back(venus_info);
		PlanetInfo* jupiter_info = PlanetInfo::create(JUPITER_NAME,0);
		jupiter_info->insertPlanetInfo();
		planet_info_list_.push_back(jupiter_info);
		PlanetInfo* mars_info = PlanetInfo::create(MARS_NAME,0);
		mars_info->insertPlanetInfo();
		planet_info_list_.push_back(mars_info);
		PlanetInfo* mercury_info = PlanetInfo::create(MERCURY_NAME,0);
		mercury_info->insertPlanetInfo();
		planet_info_list_.push_back(mercury_info);
	}
}

void StageManager::initStageInfoList(){
	executeNonQuery(StageInfo::getCreateQuery());
	Ref* itor;
	StageInfoParser parser;
	__Array* arr = executeGetMultiRecord(StageInfo::getSelectQuery(),parser);
	CCARRAY_FOREACH(arr,itor){
		StageInfo* stage_info = (StageInfo*)itor;
		stage_info_list_.push_back(stage_info);
	}
	arr->removeAllObjects();
	if (stage_info_list_.size() == 0){
		StageInfo* stage_info = StageInfo::create(MOON_NAME,1,0);
		stage_info->insertStageInfo();
		stage_info_list_.push_back(stage_info);
	}
}

PlanetInfo* StageManager::getPlanetInfoByName(const std::string& name){
	PlanetInfo* planet_info_result = nullptr;
	for (PlanetInfo* planet_info : planet_info_list_){
		if (!planet_info->getName().compare(name)){
			planet_info_result = planet_info;
		}
	}
	return planet_info_result;
}

std::vector<StageInfo*> StageManager::getStageInfosByName(const std::string& name){
	std::vector<StageInfo*> result_list;
	for (std::vector<StageInfo*>::iterator itor = stage_info_list_.begin(); itor != stage_info_list_.end(); itor++){
		StageInfo* stage_info = (StageInfo*) (*itor);
		if (!stage_info->getName().compare(name)){
			result_list.push_back(stage_info);
		}
	}
	return result_list;
}

StageInfo* StageManager::getStageInfoByStage(Stage stage){
	StageInfo* result_si = nullptr;
	for (StageInfo* stage_info : stage_info_list_){
		if (stage_info->getNo() == stage.no_ && !(stage_info->getName().compare(stage.planet_name_))){
			result_si = stage_info;
		}
	}
	return result_si;
}

BallsSetup StageManager::getBallsSetupByStage(int index){
	return (BallsSetup)balls_setup_list_.at(index - 1);
}

BallsSetup StageManager::getBallsSetupByStage(Stage stage){
	std::vector<BallsSetup> stage_balls_setup_list = balls_setup_map_.find(stage.planet_name_)->second;
	return (BallsSetup)stage_balls_setup_list.at(stage.no_-1);
}

void StageManager::addNewStageInfoList(StageInfo* stage_info){
	stage_info->insertStageInfo();
	stage_info_list_.push_back(stage_info);
}

StageManager::StageManager() {
}

StageManager::~StageManager() {
}


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
#include "../json/document.h"

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
	initializeScoreStarSetMap();
	initializeStageSetupMap();
}

void StageManager::initializeBallsSetupList(){
//	balls_setup_list_.push_back(stage_1);
}

void StageManager::initializeBallsSetupMap(){
	std::vector<BallsSetup> moon_balls_setup;
	BallsSetup stage_1;
	std::vector<std::string> row_1 = {N0, CYAN, GREEN, GREEN, GREEN, GREEN, N0, N0, N0, KEY};
	std::vector<std::string> row_2 = {N0, GREEN, GREEN, GREEN, GREEN, GREEN, N0, N0, N0};
	std::vector<std::string> row_3 = {N0, RED, RED, RED, RED, RED, N0, N0, N0, N0};
	std::vector<std::string> row_4 = {N0, RED, CYAN, RED, RED, RED, N0, N0, N0};
	stage_1 = {row_1,row_2,row_3,row_4};
	moon_balls_setup.push_back(stage_1);

	balls_setup_map_.insert(std::pair<std::string,std::vector<BallsSetup>>(MOON_NAME,moon_balls_setup));
}

void StageManager::initializeScoreStarSetMap(){
	std::vector<ScoreStarSet> moon_score_star_set;
	ScoreStarSet stage_1 = {500,1000};
	moon_score_star_set.push_back(stage_1);
	score_star_map_.insert(std::pair<std::string,std::vector<ScoreStarSet>>(MOON_NAME,moon_score_star_set));
}

void StageManager::initializeStageSetupMap(){
	std::vector<StageSetup> moon_stages_setup;
	StageSetup stage_1 = {500,1000,45,20};
	StageSetup stage_2 = {500,1000,45,20};
	StageSetup stage_3 = {500,1000,45,20};
	StageSetup stage_4 = {500,1000,45,20};
	StageSetup stage_5 = {500,1000,45,20};
	StageSetup stage_6 = {500,1000,45,20};
	StageSetup stage_7 = {500,1000,45,20};
	StageSetup stage_8 = {500,1000,45,20};
	StageSetup stage_9 = {500,1000,45,20};
	StageSetup stage_10 = {500,1000,45,20};
	StageSetup stage_11 = {500,1000,45,20};
	StageSetup stage_12 = {500,1000,45,20};
	moon_stages_setup.push_back(stage_1);
	moon_stages_setup.push_back(stage_2);
	moon_stages_setup.push_back(stage_3);
	moon_stages_setup.push_back(stage_4);
	moon_stages_setup.push_back(stage_5);
	moon_stages_setup.push_back(stage_6);
	moon_stages_setup.push_back(stage_7);
	moon_stages_setup.push_back(stage_8);
	moon_stages_setup.push_back(stage_9);
	moon_stages_setup.push_back(stage_10);
	moon_stages_setup.push_back(stage_11);
	moon_stages_setup.push_back(stage_12);
	stage_setup_map_.insert(std::pair<std::string,std::vector<StageSetup>>(MOON_NAME,moon_stages_setup));
}

ScoreStarSet StageManager::getScoreStarSetByStage(Stage stage){
	std::vector<ScoreStarSet> score_star_set_list = score_star_map_.find(stage.planet_name_)->second;
	return score_star_set_list.at(stage.no_ - 1);
}

StageSetup StageManager::getStageSetupByStage(Stage stage){
	std::vector<StageSetup> stage_setups_of_planet = stage_setup_map_.find(stage.planet_name_)->second;
	return stage_setups_of_planet.at(stage.no_ - 1);
}

BallsSetup StageManager::getBallsSetupByStageJSON(Stage stage){
	BallsSetup result;
	std::string json_file_name = stage.planet_name_ + ".json";
	std::string full_path_json_file_name = FileUtils::getInstance()->fullPathForFilename(json_file_name);
	long buffer_size = 0;
	const char* data = (const char*)FileUtils::getInstance()->getFileData(full_path_json_file_name.c_str(),"rb", &buffer_size);
	rapidjson::Document doc;
	std::string clear_data = std::string(data);
	size_t pos = clear_data.rfind("}");
	clear_data = clear_data.substr(0,pos+1);
	doc.Parse<0>(clear_data.c_str());
	delete [] data;
	rapidjson::Value& stages = doc["stages"];
	rapidjson::Value& rows = stages[stage.no_ - 1]["rows"];
	for (rapidjson::SizeType i = 0; i < rows.Size(); i++){
		rapidjson::Value& a_row = rows[i]["a_row"];
		std::vector<std::string> a_row_str;
		for (rapidjson::SizeType j = 0; j < a_row.Size(); j ++){
			a_row_str.push_back(a_row[j].GetString());
		}
		result.push_back(a_row_str);
	}
	return result;

}

void StageManager::initPlanetNameList(){
	planet_name_list_.push_back(MOON_NAME);
	planet_name_list_.push_back(VENUS_NAME);
	planet_name_list_.push_back(JUPITER_NAME);
	planet_name_list_.push_back(MARS_NAME);
	planet_name_list_.push_back(MERCURY_NAME);
}

std::string StageManager::getNextPlanetName(std::string current_planet_name){
	for (int i = 0; i < planet_name_list_.size(); i++){
		std::string a_planet_name = planet_name_list_.at(i);
		if (!a_planet_name.compare(current_planet_name)){
			if (i != (planet_name_list_.size() - 1) ){
				return planet_name_list_.at(i + 1);
			}
		}
	}
	return "no_more_planet";
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
	if (stage_info->getNo() == 1){
		PlanetInfo* planet_info = getPlanetInfoByName(stage_info->getName());
		planet_info->setIsUnlocked(true);
		planet_info->updatePlanetInfo();
	}
}

StageManager::StageManager() {
}

StageManager::~StageManager() {
}


/*
 * StageInfo.cpp
 *
 *  Created on: Sep 27, 2014
 *      Author: dudu
 */

#include "StageInfo.h"
#include "../sqlite/SqliteUtil.h"

#define STAGE_TABLE_NAME "stageinfo"
#define PLANET_NAME_KEY "planetname"
#define NO_KEY "n0"
#define STAR_NUM_KEY "starnum"

StageInfo* StageInfo::create(const std::string& name, int no, int star_num){
	StageInfo* stage_info = new StageInfo();
	if (stage_info){
		stage_info->setName(name);
		stage_info->setNo(no);
		stage_info->setStarNum(star_num);
//		stage_info->autorelease();
		return stage_info;
	}
	CC_SAFE_DELETE(stage_info);
	return stage_info;
}

const char* StageInfo::getCreateQuery(){
	return __String::createWithFormat("CREATE TABLE IF NOT EXISTS %s"
										"(%s VARCHAR(100),"
										"%s INT DEFAULT 0,"
										"%s INT DEFAULT 0);",
										STAGE_TABLE_NAME,PLANET_NAME_KEY,NO_KEY,STAR_NUM_KEY)->getCString();
}

const char* StageInfo::getSelectQuery(){
	return __String::createWithFormat("SELECT %s, %s, %s FROM %s",
										PLANET_NAME_KEY,NO_KEY,STAR_NUM_KEY,STAGE_TABLE_NAME)->getCString();
}

const char* StageInfo::getInsertQuery(){
	return __String::createWithFormat("INSERT INTO %s"
										"(%s, %s, %s)"
										" VALUES "
										"('%s',%d,%d)",
										STAGE_TABLE_NAME,PLANET_NAME_KEY,NO_KEY,STAR_NUM_KEY,
										name_.c_str(),no_,star_num_)->getCString();
}

const char* StageInfo::getUpdateQuery(){
	return __String::createWithFormat("UPDATE %s"
										" SET %s = '%s', %s = %d, %s = %d",
										STAGE_TABLE_NAME,PLANET_NAME_KEY,name_.c_str(),NO_KEY,no_,STAR_NUM_KEY,star_num_)->getCString();
}

const char* StageInfo::getDeleteQuery(){
	return __String::createWithFormat("DELETE FROM %s WHERE %s = %d",
										STAGE_TABLE_NAME,NO_KEY,no_)->getCString();
}

const char* StageInfo::getDeleteTableQuery(){
	return __String::createWithFormat("DROP TABLE %s",STAGE_TABLE_NAME)->getCString();
}

bool StageInfo::insertStageInfo(){
	return executeNonQuery(getInsertQuery());
}

bool StageInfo::updateStageInfo(){
	return executeNonQuery(getUpdateQuery());
}

bool StageInfo::deleteStagetInfo(){
	return executeNonQuery(getDeleteQuery());
}

bool StageInfo::deleteTableStageInfo(){
	return executeNonQuery(getDeleteTableQuery());
}

StageInfo::StageInfo():
no_(0),
star_num_(0)
{
	// TODO Auto-generated constructor stub
}

StageInfo::~StageInfo() {
	// TODO Auto-generated destructor stub
}


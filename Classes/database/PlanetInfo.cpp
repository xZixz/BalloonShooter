/*
 * PlanetInfo.cpp
 *
 *  Created on: Sep 27, 2014
 *      Author: dudu
 */

#include "PlanetInfo.h"
#include "../sqlite/SqliteUtil.h"

#define PLANET_TABLE_NAME "planetinfo"
#define PLANET_NAME_KEY "planetname"
#define IS_UNLOCKED_KEY "isunlocked"

PlanetInfo* PlanetInfo::create(std::string name, bool isunlocked){
	PlanetInfo* planet_info = new PlanetInfo();
	if (planet_info){
		planet_info->setName(name);
		planet_info->setIsUnlocked(isunlocked);
		return planet_info;
	}
	CC_SAFE_DELETE(planet_info);
	return nullptr;
}

const char* PlanetInfo::getCreateQuery(){
	return __String::createWithFormat("CREATE TABLE IF NOT EXISTS %s"
									"(%s VARCHAR(100),"
									"%s INT DEFAULT 0);",
									PLANET_TABLE_NAME,PLANET_NAME_KEY,IS_UNLOCKED_KEY)->getCString();
}

const char* PlanetInfo::getSelectQuery(){
	return __String::createWithFormat("SELECT %s, %s FROM %s",
										PLANET_NAME_KEY,IS_UNLOCKED_KEY,PLANET_TABLE_NAME)->getCString();
}

const char* PlanetInfo::getInsertQuery(){
	return __String::createWithFormat("INSERT INTO %s"
										"(%s, %s)"
										" VALUES "
										"('%s',%d)",
										PLANET_TABLE_NAME, PLANET_NAME_KEY, IS_UNLOCKED_KEY, name_.c_str(), isunlocked_)->getCString();
}

const char* PlanetInfo::getUpdateQuery(){
	return __String::createWithFormat("UPDATE %s"
										" SET %s = '%s', %s = %d",
										PLANET_TABLE_NAME, PLANET_NAME_KEY, name_.c_str(), IS_UNLOCKED_KEY, isunlocked_)->getCString();
}

const char* PlanetInfo::getDeleteQuery(){
	return __String::createWithFormat("DELETE FROM %s WHERE %s = '%s'",
										PLANET_TABLE_NAME, PLANET_NAME_KEY, name_.c_str())->getCString();
}

const char* PlanetInfo::getDeleteTableQuery(){
	return __String::createWithFormat("DROP TABLE %s", PLANET_TABLE_NAME)->getCString();
}

bool PlanetInfo::insertPlanetInfo(){
	return executeNonQuery(getInsertQuery());
}

bool PlanetInfo::updatePlanetInfo(){
	return executeNonQuery(getUpdateQuery());
}

bool PlanetInfo::deletePlanetInfo(){
	return executeNonQuery(getDeleteQuery());
}

bool PlanetInfo::deleteTablePlanetInfo(){
	return executeNonQuery(getDeleteTableQuery());
}

PlanetInfo::PlanetInfo():
isunlocked_(false)
{
}

PlanetInfo::~PlanetInfo() {
}


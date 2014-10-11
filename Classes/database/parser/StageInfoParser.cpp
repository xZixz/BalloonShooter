/*
 * StageInfoParser.cpp
 *
 *  Created on: Oct 4, 2014
 *      Author: dudu
 */

#include "StageInfoParser.h"
#include "../StageInfo.h"

Ref* StageInfoParser::parse(SQLite::Statement& statement){
	return StageInfo::create(statement.getColumn(0).getText(),statement.getColumn(1).getInt(),statement.getColumn(2).getInt());
}

StageInfoParser::StageInfoParser() {
}

StageInfoParser::~StageInfoParser() {
}


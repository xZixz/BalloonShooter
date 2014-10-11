/*
 * PlanetInfoParser.cpp
 *
 *  Created on: Sep 27, 2014
 *      Author: dudu
 */

#include "PlanetInfoParser.h"
#include "../PlanetInfo.h"

Ref* PlanetInfoParser::parse(SQLite::Statement& statement){
	return PlanetInfo::create(statement.getColumn(0).getText(),statement.getColumn(1).getInt());
}

PlanetInfoParser::PlanetInfoParser() {
}

PlanetInfoParser::~PlanetInfoParser() {
}


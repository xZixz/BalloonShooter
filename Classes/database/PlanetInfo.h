/*
 * PlanetInfo.h
 *
 *  Created on: Sep 27, 2014
 *      Author: dudu
 */

#ifndef PLANETINFO_H_
#define PLANETINFO_H_

#include "cocos2d.h"

USING_NS_CC;

class PlanetInfo : public Ref {
public:

	static PlanetInfo* create(std::string name, bool isunlocked);

	static const char* getCreateQuery();
	static const char* getSelectQuery();
	const char* getInsertQuery();
	const char* getUpdateQuery();
	const char* getDeleteQuery();
	const char* getDeleteTableQuery();

	bool insertPlanetInfo();
	bool updatePlanetInfo();
	bool deletePlanetInfo();
	bool deleteTablePlanetInfo();

	PlanetInfo();
	virtual ~PlanetInfo();

	CC_SYNTHESIZE(std::string,name_,Name);
	CC_SYNTHESIZE(bool,isunlocked_,IsUnlocked);

};

#endif /* PLANETINFO_H_ */

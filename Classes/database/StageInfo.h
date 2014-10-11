/*
 * StageInfo.h
 *
 *  Created on: Sep 27, 2014
 *      Author: dudu
 */

#ifndef STAGEINFO_H_
#define STAGEINFO_H_

#include "cocos2d.h"

USING_NS_CC;

class StageInfo : public Ref {
public:

	static StageInfo* create(const std::string& name, int no, int star_num);

	static const char* getCreateQuery();
	static const char* getSelectQuery();
	const char* getInsertQuery();
	const char* getUpdateQuery();
	const char* getDeleteQuery();
	const char* getDeleteTableQuery();

	bool insertStageInfo();
	bool updateStageInfo();
	bool deleteStagetInfo();
	bool deleteTableStageInfo();

	StageInfo();
	virtual ~StageInfo();
	CC_SYNTHESIZE(std::string,name_,Name);
	CC_SYNTHESIZE(int,no_,No);
	CC_SYNTHESIZE(int,star_num_,StarNum);
};

#endif /* STAGEINFO_H_ */

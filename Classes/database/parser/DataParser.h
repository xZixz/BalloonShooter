/*
 * DataParser.h
 *
 *  Created on: Mar 17, 2014
 *      Author: nobugz
 */

#ifndef DATAPARSER_H_
#define DATAPARSER_H_

#include "../../sqlite/SQLiteC++.h"
#include "cocos2d.h"

USING_NS_CC;

class DataParser {
public:
	virtual ~DataParser();
	virtual Ref* parse(SQLite::Statement& statement) = 0;
};

#endif /* DATAPARSER_H_ */

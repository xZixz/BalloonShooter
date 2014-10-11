/*
 * SqliteUtil.h
 *
 *  Created on: Mar 17, 2014
 *      Author: nobugz
 */

#ifndef SQLITEUTIL_H_
#define SQLITEUTIL_H_

#include "../database/parser/DataParser.h"

bool executeNonQuery(const char* commandText);

Ref* executeGetOneRecord(const char* commandText, DataParser& parser);

__Array* executeGetMultiRecord(const char* commandText, DataParser& parser);

cocos2d::Vector<Ref*> executeGetMultiRecord2(const char* commandText, DataParser& parser);
#endif /* SQLITEUTIL_H_ */

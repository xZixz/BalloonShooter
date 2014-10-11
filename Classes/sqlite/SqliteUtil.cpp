/*
 * SqliteUtil.cpp
 *
 *  Created on: Mar 17, 2014
 *      Author: nobugz
 */

#include "SqliteUtil.h"
#include "cocos2d.h"
#include "../sqlite/SQLiteC++.h"

USING_NS_CC;

#define DATABASE_NAME "balloonshooter"

const char* getDatabaseName();

bool executeNonQuery(const char* commandText) {
	CCLOG("EXECUTE QUERY: %s", commandText);
	try {
		SQLite::Database db(getDatabaseName(), SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE);
		SQLite::Transaction transaction(db);
		db.exec(commandText);
		transaction.commit();

		return true;
	} catch (std::exception &e) {
		CCLOG("EXCEPTION EXECUTE NON QUERY: %s", commandText);
	}

	return false;
}

Ref* executeGetOneRecord(const char* commandText, DataParser& parser) {
	CCLOG("EXECUTE QUERY: %s", commandText);
	try {
		SQLite::Database db(getDatabaseName(), SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE);
		log("executeGetOneRecord1");
		SQLite::Statement query(db, commandText);
		log("executeGetOneRecord1");
		if(!query.executeStep()){
			log("executeGetOneRecord3");
			return NULL;
		}

		log("executeGetOneRecord4");
		return parser.parse(query);
	} catch (std::exception &e) {
		log("executeGetOneRecord error %s", e.what());
		CCLOG("EXCEPTION EXECUTE NON QUERY: %s", commandText);
	}
	return NULL;
}

__Array* executeGetMultiRecord(const char* commandText, DataParser& parser) {
	CCLOG("EXECUTE QUERY: %s", commandText);
	__Array* arrResult = __Array::create();
	try {
		SQLite::Database db(getDatabaseName(), SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE);
		SQLite::Statement query(db, commandText);

		while (query.executeStep()) {
			Ref* obj = parser.parse(query);
			if (obj) {
				arrResult->addObject(obj);
			}
		}
	} catch (std::exception &e) {
		CCLOG("EXCEPTION EXECUTE NON QUERY: %s", commandText);
	}

	return arrResult;
}

cocos2d::Vector<Ref*> executeGetMultiRecord2(const char* commandText, DataParser& parser) {
	CCLOG("EXECUTE QUERY: %s", commandText);
	cocos2d::Vector<Ref*> vectorResult;
	try {
		SQLite::Database db(getDatabaseName(), SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE);
		SQLite::Statement query(db, commandText);

		while (query.executeStep()) {
			Ref* obj = parser.parse(query);
			if (obj) {
				vectorResult.pushBack(obj);
			}
		}
	} catch (std::exception &e) {
		CCLOG("EXCEPTION EXECUTE NON QUERY: %s", commandText);
	}

	return vectorResult;
}

const char* getDatabaseName() {
	__String filePath =  FileUtils::getInstance()->getWritablePath();
	__String* newDbPath= __String::createWithFormat("%s/%s", filePath.getCString(),DATABASE_NAME);
	return newDbPath->getCString();
}

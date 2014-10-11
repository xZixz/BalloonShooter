/*
 * StageInfoParser.h
 *
 *  Created on: Oct 4, 2014
 *      Author: dudu
 */

#ifndef STAGEINFOPARSER_H_
#define STAGEINFOPARSER_H_

#include "DataParser.h"

class StageInfoParser : public DataParser {
public:

	virtual Ref* parse(SQLite::Statement& statement);

	StageInfoParser();
	virtual ~StageInfoParser();
};

#endif /* STAGEINFOPARSER_H_ */

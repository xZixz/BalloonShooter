/*
 * PlanetInfoParser.h
 *
 *  Created on: Sep 27, 2014
 *      Author: dudu
 */

#ifndef PLANETINFOPARSER_H_
#define PLANETINFOPARSER_H_

#include "DataParser.h"

class PlanetInfoParser : public DataParser {
public:

	virtual Ref* parse(SQLite::Statement& statement);

	PlanetInfoParser();
	virtual ~PlanetInfoParser();
};

#endif /* PLANETINFOPARSER_H_ */

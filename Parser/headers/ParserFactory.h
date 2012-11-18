/* 
 * File:   ParserFactory.h
 * Author: e094326d
 *
 * Created on 18 novembre 2012, 10:32
 */

#ifndef PARSERFACTORY_H
#define	PARSERFACTORY_H

#include "../../main/headers/common.h"

class ParserFactory {
public:
	ParserFactory();
	virtual ~ParserFactory();
	
	virtual Parser createParser() = 0;
};

#endif	/* PARSERFACTORY_H */
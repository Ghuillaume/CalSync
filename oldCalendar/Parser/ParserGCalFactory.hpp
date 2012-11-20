/* 
 * File:   ParserGCalFactory.h
 * Author: e094326d
 *
 * Created on 18 novembre 2012, 11:57
 */

#ifndef PARSERGCALFACTORY_H
#define	PARSERGCALFACTORY_H

#include "ParserFactory.hpp"
#include "../Model/common.h"

class ParserGCalFactory : public ParserFactory {
public:
	ParserGCalFactory();
	virtual ~ParserGCalFactory();
	
	Parser* createParser();
};

#endif	/* PARSERGCALFACTORY_H */


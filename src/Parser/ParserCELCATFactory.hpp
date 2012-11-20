/* 
 * File:   ParserCELCATFactory.h
 * Author: e094326d
 *
 * Created on 18 novembre 2012, 13:08
 */

#ifndef PARSERCELCATFACTORY_H
#define	PARSERCELCATFACTORY_H

#include "ParserFactory.hpp"
#include "Parser.hpp"

class ParserCELCATFactory : public ParserFactory{
public:
	ParserCELCATFactory();
	virtual ~ParserCELCATFactory();
	
	Parser* createParser();
};

#endif	/* PARSERCELCATFACTORY_H */


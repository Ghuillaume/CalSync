/* 
 * File:   Parser.h
 * Author: e094326d
 *
 * Created on 18 novembre 2012, 11:55
 */

#ifndef PARSER_H
#define	PARSER_H

#include <string>
#include "../Model/Model.hpp"

class Parser {

    public:
        Parser(){};
        virtual ~Parser(){};

        virtual void getEventList() = 0;
        virtual void clearCalendar() = 0;
        virtual void exportEvent(const QString & title,
                                 const QString & description,
                                 const QString & location,
                                 const Time* start,
                                 const Time* end) = 0;

    protected:
        virtual void parseEvents(QByteArray in) = 0;

        Model* model;



};

#endif	/* PARSER_H */


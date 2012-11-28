/*
 * File:   ParserCELCAT.h
 * Author: e094326d
 *
 * Created on 18 novembre 2012, 13:24
 */

#ifndef PARSERCELCAT_H
#define	PARSERCELCAT_H

#include <QHttp>
#include <QObject>
#include <QByteArray>

#include "Parser.hpp"
#include "../Model/common.h"
#include "../Model/Model.hpp"


class ParserCELCAT : public QObject, public Parser {

    Q_OBJECT

    public:
        ParserCELCAT(string url, bool ssl, Model* model, QObject* parent);
        virtual ~ParserCELCAT();

        virtual void getEventList();


    public slots:
        void stateChanged ( int state );
        void responseHeaderReceived ( const QHttpResponseHeader & resp );
        void requestFinished ( int id, bool error );

    private:
        virtual void parseEvents(QByteArray in);

        QHttp* query;
};

#endif	/* PARSERCELCAT_H */


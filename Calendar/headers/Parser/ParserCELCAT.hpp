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
#include <QNetworkReply>
#include <QNetworkAccessManager>
#include <./lib/qjson/include/QJson/Parser>
#include <QtCore>

#include "Parser.hpp"
#include "../Model/common.h"
#include "../Model/Model.hpp"


class ParserCELCAT : public QObject, public Parser {

    Q_OBJECT

    public:
        ParserCELCAT(QString groupId, Model* model, QObject* parent);
        virtual ~ParserCELCAT();

        virtual void getEventList();

    public slots:
        void stateChanged ( int state );
        void responseHeaderReceived ( const QHttpResponseHeader & resp );
        void replyFinished(QNetworkReply*);

    private:
        virtual void parseEvents(QByteArray in);

        QString groupId;

        QHttp* query;
        QNetworkAccessManager* networkManager;
};

#endif	/* PARSERCELCAT_H */


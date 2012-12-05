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
#include <QtCore>
#include <QString>


#include <./lib/qjson/include/QJson/Parser>
#include "lib/qjson/include/QJson/Serializer" //src/serializerrunnable.h"
#include "Parser.hpp"
#include "../Model/Model.hpp"
#include "../Model/common.h"
#include "../Model/Time.hpp"
#include "../Controller/Controller.hpp"


class ParserCELCAT : public QObject, public Parser {

    Q_OBJECT

    public:
        ParserCELCAT(QString groupId, Model* model, QObject* parent, Controller* controller);
        virtual ~ParserCELCAT();

        virtual void getEventList();
        virtual void clearCalendar();
        virtual void exportEvent(const QString & title,
                                 const QString & description,
                                 const QString & location,
                                 const Time* start,
                                 const Time* end);

    public slots:
        void replyFinished(QNetworkReply*);

    signals:
        void sendMessage(QString, int);

    private:
        virtual void parseEvents(QByteArray in);

        QString groupId;

        QNetworkAccessManager* networkManager;
        Controller* controller;
};

#endif	/* PARSERCELCAT_H */


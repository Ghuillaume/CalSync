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
        ParserCELCAT(QString groupId, Model* model, QObject* parent);
        virtual ~ParserCELCAT();

        virtual void getEventList();
        virtual void clearCalendar();
        virtual void exportEvent(const QString & title,
                                 const QString & description,
                                 const Time* start,
                                 const Time* end);

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


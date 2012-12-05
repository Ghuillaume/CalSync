#ifndef PARSERGCAL_HPP
#define PARSERGCAL_HPP

#include <QHttp>
#include <QObject>
#include <QByteArray>
#include <QNetworkReply>
#include <QNetworkAccessManager>
#include <./lib/qjson/include/QJson/Parser>
#include <QtCore>

#include "Parser.hpp"
#include "../Model/Model.hpp"
#include "../Model/common.h"
#include "../Model/Time.hpp"
#include "../Controller/Controller.hpp"

class Controller;

// DINGO !!!
// 30min perdue sur une putain d'erreur, faut pas mettre :
// class ParserGCal : public Parser, public QObject {
// mais :
class ParserGCal : public QObject, public Parser {

    Q_OBJECT

    public:
        ParserGCal(QString id, QString authToken, Model* model, QObject* parent, Controller* controller);
        virtual ~ParserGCal();

        virtual void getEventList();
        virtual void clearCalendar();
        void exportEvent(const QString & title, const QString & description, const QString & location, const Time* start, const Time* end);
		Time* buildDate(QString &strDate);

    public slots:
        void replyFinished(QNetworkReply*);

    signals:
        void sendMessage(QString, int);

    private:
        virtual void parseEvents(QByteArray in);

        QString id;
        QString authToken;

        QNetworkAccessManager* networkManager;
        Controller* controller;
		
		QVariantList m_calendars;
		QVariantList m_events;

        int requests;
        int replies;
};

#endif // PARSERGCAL_HPP

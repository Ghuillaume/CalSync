#ifndef PARSERGCAL_HPP
#define PARSERGCAL_HPP

#include <QHttp>
#include <QObject>
#include <QByteArray>

#include "Parser.hpp"
#include "../Model/Model.hpp"
#include "../Model/common.h"
#include "../Controler/Controler.hpp"

class Controler;

// DINGO !!!
// 30min perdue sur une putain d'erreur, faut pas mettre :
// class ParserGCal : public Parser, public QObject {
// mais :
class ParserGCal : public QObject, public Parser {

    Q_OBJECT

    public:
        ParserGCal(string url, bool ssl, string id, string apikey, Model* model, QObject* parent);
        virtual ~ParserGCal();

        virtual void getEventList();


    public slots:
        void stateChanged ( int state );
        void responseHeaderReceived ( const QHttpResponseHeader & resp );
        void requestFinished ( int id, bool error );

    private:
        virtual void parseEvents(QByteArray in);

        string id;
        string apiKey;
        QHttp* query;


};

#endif // PARSERGCAL_HPP
/* 
 * File:   ParserCELCAT.cpp
 * Author: e094326d
 * 
 * Created on 18 novembre 2012, 13:24
 */

#include "../../headers/Parser/ParserCELCAT.hpp"

ParserCELCAT::ParserCELCAT(string url, bool ssl, string groupId, Model* model, QObject* parent) : QObject(parent) {
    this->url = url;
    this->ssl = ssl;
    this->groupId = groupId;
    this->model = model;

    query = new QHttp(this);
    connect(query, SIGNAL(stateChanged(int)), this, SLOT(stateChanged(int)));
    connect(query, SIGNAL(responseHeaderReceived(QHttpResponseHeader)), this, SLOT(responseHeaderReceived(QHttpResponseHeader)));
    connect(query, SIGNAL(requestFinished(int,bool)), this, SLOT(requestFinished(int,bool)));
}

ParserCELCAT::~ParserCELCAT() {
}



// NOT WORKING !!!!!
void ParserCELCAT::getEventList() {
    qCritical() << "Getting events from CELCAT";

    QString queryString = QString(this->groupId.c_str()) + ".ics";
    qDebug() << "Query string = " << queryString;
    query->setHost(this->url.c_str(), (this->ssl ? QHttp::ConnectionModeHttps : QHttp::ConnectionModeHttps) );
    query->get(queryString);

    // TODO : timeout !!!!
}


void ParserCELCAT::parseEvents(QByteArray in) {
    qDebug() << in;

    qCritical() << "Parsing events TODO" << endl;
}

void ParserCELCAT::stateChanged(int state)   {
    switch(state)   {
    case 0:
        qDebug() << "Unconnected";
        break;
    case 1:
        qDebug() << "Host Lookup";
        break;
    case 2:
        qDebug() << "Connecting";
        break;
    case 3:
        qDebug() << "Sending";
        break;
    case 4:
        qDebug() << "Reading";
        break;
    case 5:
        qDebug() << "Connect";
        break;
    case 6:
        qDebug() << "Closing";
        break;
    }
}

void ParserCELCAT::responseHeaderReceived(const QHttpResponseHeader &resp)   {
    qDebug() << "Size : " << resp.contentLength();
    qDebug() << "Type : " << resp.contentType();
    qDebug() << "Status Code : " << resp.statusCode();
}

void ParserCELCAT::requestFinished(int id, bool error)   {
    qDebug() << "Request Id : " << id;
    if(error)   {
        qDebug() << "Error";
    }   else    {
        QByteArray in = query->readAll();
        this->parseEvents(in);
    }
}

/* 
 * File:   ParserCELCAT.cpp
 * Author: e094326d
 * 
 * Created on 18 novembre 2012, 13:24
 */

#include "../../headers/Parser/ParserCELCAT.hpp"

ParserCELCAT::ParserCELCAT(string url, bool ssl, Model* model, QObject* parent) : QObject(parent) {
    this->url = url;
    this->ssl = ssl;
    this->model = model;

    query = new QHttp(this);
    connect(query, SIGNAL(stateChanged(int)), this, SLOT(stateChanged(int)));
    connect(query, SIGNAL(responseHeaderReceived(QHttpResponseHeader)), this, SLOT(responseHeaderReceived(QHttpResponseHeader)));
    connect(query, SIGNAL(requestFinished(int,bool)), this, SLOT(requestFinished(int,bool)));
}

ParserCELCAT::~ParserCELCAT() {
}



void ParserCELCAT::getEventList() {

    qCritical() << "Getting events TODO" << endl;
}


void ParserCELCAT::parseEvents(QByteArray in) {

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
        qDebug() << in;
        this->parseEvents(in);
    }
}

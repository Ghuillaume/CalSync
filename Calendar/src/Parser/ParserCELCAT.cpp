/* 
 * File:   ParserCELCAT.cpp
 * Author: e094326d
 * 
 * Created on 18 novembre 2012, 13:24
 */

#include "../../headers/Parser/ParserCELCAT.hpp"

ParserCELCAT::ParserCELCAT(QString groupId, Model* model, QObject* parent) : QObject(parent) {
    this->groupId = groupId;
    this->model = model;

    query = new QHttp(this);
    connect(query, SIGNAL(stateChanged(int)), this, SLOT(stateChanged(int)));
    connect(query, SIGNAL(responseHeaderReceived(QHttpResponseHeader)), this, SLOT(responseHeaderReceived(QHttpResponseHeader)));

    networkManager = new QNetworkAccessManager(this);
    connect(networkManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished(QNetworkReply*)));
}

ParserCELCAT::~ParserCELCAT() {
}


void ParserCELCAT::getEventList() {

    QString url = QString("http://www.edt-sciences.univ-nantes.fr/%1.xml").arg(this->groupId);
    //QApplication::setOverrideCursor(Qt::WaitCursor);
    networkManager->get(QNetworkRequest(QUrl(url)));
    qDebug() << "Getting events from CELCAT";
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

void ParserCELCAT::replyFinished(QNetworkReply * reply)
{
    //QApplication::restoreOverrideCursor();
    QByteArray in = reply->readAll();
    qDebug() << in;
    this->parseEvents(in);
}

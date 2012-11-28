
#include "../../headers/Parser/ParserGCal.hpp"

ParserGCal::ParserGCal(string url, bool ssl, string id, string apikey, Model *model, QObject* parent) : QObject(parent) {
    this->url = url;
    this->ssl = ssl;
    this->id = id;
    this->apiKey = apikey;
    this->model = model;

    query = new QHttp(this);
    connect(query, SIGNAL(stateChanged(int)), this, SLOT(stateChanged(int)));
    connect(query, SIGNAL(responseHeaderReceived(QHttpResponseHeader)), this, SLOT(responseHeaderReceived(QHttpResponseHeader)));
    connect(query, SIGNAL(requestFinished(int,bool)), this, SLOT(requestFinished(int,bool)));
}

ParserGCal::~ParserGCal() {

}

void ParserGCal::getEventList() {
    qDebug() << "Getting events from Google Calendar";

    QString queryString = "/calendar/v3/calendars/" +
            QString(this->id.c_str()) +
            "/events?key=" + QString(this->apiKey.c_str());
    qDebug() << "Query string = " << queryString;
    query->setHost(this->url.c_str(), (this->ssl ? QHttp::ConnectionModeHttps : QHttp::ConnectionModeHttps) );
    query->get(queryString);

    // TODO : timeout, sinon quand google répond pas ben ça fait que dalle, pas de message d'erreur etc !!!!
}

void ParserGCal::parseEvents(QByteArray in) {

    qCritical() << "Parsing events TODO";
}



void ParserGCal::stateChanged(int state)   {
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

void ParserGCal::responseHeaderReceived(const QHttpResponseHeader &resp)   {
    qDebug() << "Size : " << resp.contentLength();
    qDebug() << "Type : " << resp.contentType();
    qDebug() << "Status Code : " << resp.statusCode();
}

void ParserGCal::requestFinished(int id, bool error)   {
    qDebug() << "Request Id : " << id;
    if(error)   {
        qDebug() << "Error";
    }   else    {
        QByteArray in = query->readAll();
        qDebug() << in;
        this->parseEvents(in);
    }
}

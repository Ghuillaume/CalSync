
#include <qt4/QtNetwork/qhttp.h>

#include "../../headers/Parser/ParserGCal.hpp"

ParserGCal::ParserGCal(string url, bool ssl, string id, string apikey, string authToken, Model *model, QObject* parent) : QObject(parent) {
    this->url = url;
    this->ssl = ssl;
    this->id = id;
    this->apiKey = apikey;
    this->authToken = authToken;
    this->model = model;

    query = new QHttp(this);
    connect(query, SIGNAL(stateChanged(int)), this, SLOT(stateChanged(int)));
    connect(query, SIGNAL(responseHeaderReceived(QHttpResponseHeader)), this, SLOT(responseHeaderReceived(QHttpResponseHeader)));
    connect(query, SIGNAL(requestFinished(int,bool)), this, SLOT(requestFinished(int,bool)));

    networkManager = new QNetworkAccessManager(this);
    connect(networkManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished(QNetworkReply*)));
    
}

ParserGCal::~ParserGCal() {

}

void ParserGCal::replyFinished(QNetworkReply * reply)
{
    QApplication::restoreOverrideCursor();
    qDebug() << reply->readAll();
}

QString ParserGCal::buildQuery() {

    return QString("/calendar/v3/calendars/%1/events?key=%2")
             .arg(this->id.c_str())
             .arg(this->apiKey.c_str());
}

void ParserGCal::getEventList() {
    qDebug() << "Getting events from Google Calendar";

    // Works if OAuth not required
    /*query->setHost(this->url.c_str(), (this->ssl ? QHttp::ConnectionModeHttps : QHttp::ConnectionModeHttps) );
    query->get(this->buildQuery());*/

    QString s = QString("https://www.googleapis.com/calendar/v3/calendars/%1/events").arg(this->id.c_str());
    QUrl url;
    url.setEncodedUrl(QUrl::toPercentEncoding(s, "/:"));

    QNetworkRequest request;
    request.setUrl(url);
    request.setRawHeader("Authorization", QString("OAuth %1").arg(this->authToken.c_str()).toLatin1());
    qDebug() << "Header = " << "Authorization" << QString("OAuth %1").arg(this->authToken.c_str()).toLatin1();

    QApplication::setOverrideCursor(Qt::WaitCursor);
    networkManager->get(request);

    // TODO : timeout, sinon quand google répond pas ben ça fait que dalle, pas de message d'erreur etc !!!!
}

void ParserGCal::parseEvents(QByteArray in) {
    qDebug() << in;

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
        this->parseEvents(in);
    }
}

#include "../../headers/Parser/ParserGCal.hpp"

ParserGCal::ParserGCal(string url, bool ssl, string id, string authToken, Model *model, QObject* parent) : QObject(parent) {
    this->url = url;
    this->ssl = ssl;
    this->id = id;
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

    return QString("/calendar/v3/calendars/%1/events?key=AIzaSyDNTR8D9cS5lQOqVW5dX1dFpKgQqlKA9sM")
             .arg(this->id.c_str());
}

void ParserGCal::getEventList() {
    qDebug() << "Getting events from Google Calendar";

    // Works if OAuth not required
    query->setHost(this->url.c_str(), (this->ssl ? QHttp::ConnectionModeHttps : QHttp::ConnectionModeHttps) );
    query->get(this->buildQuery());

    /*QString s = QString("https://www.googleapis.com/calendar/v3/calendars/%1/events").arg(this->id.c_str());
    QUrl url;
    url.setEncodedUrl(QUrl::toPercentEncoding(s, "/:"));

    QNetworkRequest request;
    request.setUrl(url);
    request.setRawHeader("Authorization", QString("OAuth %1").arg(this->authToken.c_str()).toLatin1());
    qDebug() << "Header = " << "Authorization" << QString("OAuth %1").arg(this->authToken.c_str()).toLatin1();

    QApplication::setOverrideCursor(Qt::WaitCursor);
    networkManager->get(request);*/

    // TODO : timeout, sinon quand google répond pas ben ça fait que dalle, pas de message d'erreur etc !!!!
}

void ParserGCal::parseEvents(QByteArray in) {
	QJson::Parser parser;
	bool ok = FALSE;

	QVariant result = parser.parse (in, &ok).toMap();
	if (!ok) {
	  qFatal("An error occurred during parsing");
	} else {
		if(result.toMap().contains("error"))
		{
			qDebug() << "ERROR occured:\n";
			return;
		} 
		// If we parse events of a calendar
		else if(result.toMap()["kind"].toString() == "calendar#events") {
			m_events = result.toMap()["items"].toList();
			// for all events, build the slot
			for(int i = 0; i < m_events.count(); ++i)
			{
				// Build the title from string "summary"
				QVariantMap mapEvents = m_events[i].toMap();
				string eventName = mapEvents["summary"].toString().toStdString();
				// Build the timeBegin from start date string
				QVariantMap nestedMap = mapEvents["start"].toMap();
				QString dateBegin = nestedMap["dateTime"].toString();
				Time* timeBegin = this->buildDate(dateBegin);
				// Build the timeEnd from end date string
				nestedMap = mapEvents["end"].toMap();
				QString dateEnd = nestedMap["dateTime"].toString();
				Time* timeEnd = this->buildDate(dateEnd);
				// Create slot with previous variables
				this->model->createSlot(timeBegin, timeEnd, eventName, "");
			}
		}
	}
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

Time* ParserGCal::buildDate(QString &strDate) {
	int year = 0;
	int month = 0;
	int day = 0;
	int hour = 0;
	int minute = 0;
	char t = 'T';
	if (strDate.contains(QChar(t), Qt::CaseSensitive)) {
		ListOfString strings = explode(strDate.toStdString(), t);
		
		ListOfString date = explode(strings[0], '-');
		year = atoi(date[0].c_str());
		month = atoi(date[1].c_str());
		day = atoi(date[2].c_str());
		
		ListOfString date2 = explode(strings[1], ':');
		hour = atoi(date2[0].c_str());
		minute = atoi(date2[1].c_str());
	}
	return new Time(minute, hour, day, month, year);
}
#include "../../headers/Parser/ParserGCal.hpp"

/**
 * ParserGCal(QString id, QString authToken, Model *model, QObject* parent, Controller* controller)
 * ParserGCal constructor
 * Precondition : /
 * Postcondition : /
 */
ParserGCal::ParserGCal(QString id, QString authToken, Model *model, QObject* parent, Controller* controller) : QObject(parent) {
    this->id = id;
    this->authToken = authToken;
    this->model = model;

    this->controller = controller;

    networkManager = new QNetworkAccessManager(this);
    QObject::connect(networkManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished(QNetworkReply*)));
    QObject::connect(this, SIGNAL(sendMessage(QString, int)), this->controller->getView()->statusbar, SLOT(showMessage(QString, int)));
    
    requests = 0;
    replies = 0;
}

ParserGCal::~ParserGCal() {

}


void ParserGCal::replyFinished(QNetworkReply * reply)
{
    replies++;

    QApplication::restoreOverrideCursor();
    QByteArray in = reply->readAll();
    qDebug() << "REPLY : " << in;
    this->parseEvents(in);

    if( (this->controller->getView()->statusbar->currentMessage() == "Clearing Google Calendar..."
            || this->controller->getView()->statusbar->currentMessage() == "Getting event list from Google Calendar..."
            || this->controller->getView()->statusbar->currentMessage() == "Exporting event list to Google Calendar...")
        && requests == replies) {

        this->controller->getView()->statusbar->clearMessage();
    }
}
void ParserGCal::clearCalendar() {

    requests++;

    emit sendMessage(QString("Clearing Google Calendar..."), 0);

    // todo : Amélioration possible : récupérer tous les events avec
    // "\"extendedProperties\": \n{ \"shared\": \n{ \"fromMyCalendar\": \"true\"\n}\n},\n"
    // pour ne supprimer que ceux là :)

    QString s = QString("https://www.googleapis.com/calendar/v3/calendars/%1/clear").arg(this->id);
    QUrl url;
    url.setEncodedUrl(QUrl::toPercentEncoding(s, "/:"));

    QNetworkRequest request;
    request.setUrl(url);
    request.setRawHeader("Authorization", QString("OAuth %1").arg(this->authToken).toLatin1());
    request.setRawHeader("X-JavaScript-User-Agent", "Google APIs Explorer");

    QApplication::setOverrideCursor(Qt::WaitCursor);
    networkManager->get(request);
}

void ParserGCal::getEventList() {

    requests++;

    emit sendMessage(QString("Getting event list from Google Calendar..."), 0);

    qDebug() << "Getting events from Google Calendar";

    QString s = QString("https://www.googleapis.com/calendar/v3/calendars/%1/events").arg(this->id);
    QUrl url;
    url.setEncodedUrl(QUrl::toPercentEncoding(s, "/:"));

    QNetworkRequest request;
    request.setUrl(url);
    request.setRawHeader("Authorization", QString("OAuth %1").arg(this->authToken).toLatin1());
    request.setRawHeader("X-JavaScript-User-Agent", "Google APIs Explorer");

    QApplication::setOverrideCursor(Qt::WaitCursor);
    networkManager->get(request);
}

void ParserGCal::exportEvent(const QString & title, const QString & description, const QString & location, const Time* start, const Time* end)
{
    requests++;

    emit sendMessage(QString("Exporting event list to Google Calendar..."), 0);

    QString s = QString("https://www.googleapis.com/calendar/v3/calendars/%1/events").arg(this->id);
    QUrl url;
    url.setEncodedUrl(QUrl::toPercentEncoding(s, "/:"));

    QNetworkRequest request;
    request.setUrl(url);
    request.setRawHeader("Authorization", QString("OAuth %1").arg(this->authToken).toLatin1());
    request.setRawHeader("Content-Type", "application/json");

    QString strStart = QString("%1-%2-%3T%4:%5:00Z")
            .arg(start->getYear())
            .arg(start->getMonth())
            .arg(start->getDay())
            .arg(start->getHour()-1)
            .arg(start->getMinute());
    QString strEnd = QString("%1-%2-%3T%4:%5:00Z")
            .arg(end->getYear())
            .arg(end->getMonth())
            .arg(end->getDay())
            .arg(end->getHour())
            .arg(end->getMinute());
    QString query = QString("{\n") +
            QString("\"end\": \n{ \"dateTime\": \"%1\"\n},\n").arg(strEnd) +
            QString("\"start\": \n{ \"dateTime\": \"%1\" \n},\n").arg(strStart) +
            QString("\"summary\": \"%1\",\n").arg(title) +
            QString("\"description\": \"%1\",\n").arg(description) +
            QString("\"location\": \"%1\",\n").arg(location) +
            QString("\"extendedProperties\": {\n \"shared\": {\n \"fromMyCalendar\": \"true\"\n}\n}\n") +
            QString("}");
    QByteArray params = query.toUtf8();
    qDebug() << "Params to send" << params;


    QApplication::setOverrideCursor(Qt::WaitCursor);
    networkManager->post(request, params);

}

/**
 * void parseEvents(QByteArray in)
 * Build an event
 * Precondition : The event is well-formed
 * Postcondition : /
 */
void ParserGCal::parseEvents(QByteArray in) {
	QJson::Parser parser;
	bool ok = FALSE;

	QVariant result = parser.parse (in, &ok).toMap();
	if (!ok) {
      qCritical("An error occurred during parsing");
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
                string eventDescription = mapEvents["description"].toString().toStdString();
                string eventLocation = mapEvents["location"].toString().toStdString();
				// Build the timeBegin from start date string
				QVariantMap nestedMap = mapEvents["start"].toMap();
				QString dateBegin = nestedMap["dateTime"].toString();
				Time* timeBegin = this->buildDate(dateBegin);
				// Build the timeEnd from end date string
				nestedMap = mapEvents["end"].toMap();
				QString dateEnd = nestedMap["dateTime"].toString();
				Time* timeEnd = this->buildDate(dateEnd);
				// Create slot with previous variables
                this->model->createSlot(timeBegin, timeEnd, eventName, eventDescription, eventLocation);
			}
            this->controller->getView()->display();
		}
        else if(result.toMap()["kind"].toString() == "calendar#calendarList")
        {
            m_calendars = result.toMap()["items"].toList();
            for(int i = 0; i < m_calendars.count(); ++i)
            {
                qDebug() << m_calendars[i].toString();
            }
        }
    }
}

/*
 * Time* buildDate(QString &strDate)
 * Create a Time object from a string date
 * Precondition : The string date is well-formed (dd-mm-yyyyThh:MM)
 * Postcondition : /
 */
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

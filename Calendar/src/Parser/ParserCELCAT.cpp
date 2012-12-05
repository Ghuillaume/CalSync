/* 
 * File:   ParserCELCAT.cpp
 * Author: e094326d
 * 
 * Created on 18 novembre 2012, 13:24
 */

#include "../../headers/Parser/ParserCELCAT.hpp"

ParserCELCAT::ParserCELCAT(QString groupId, Model* model, QObject* parent, Controller* controller) : QObject(parent) {
    this->groupId = groupId;
    this->model = model;
    this->controller = controller;

    networkManager = new QNetworkAccessManager(this);
    QObject::connect(networkManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished(QNetworkReply*)));
    QObject::connect(this, SIGNAL(sendMessage(QString, int)), this->controller->getView()->statusbar, SLOT(showMessage(QString, int)));
}

ParserCELCAT::~ParserCELCAT() {
}


void ParserCELCAT::getEventList() {

    emit sendMessage(QString("Getting event list from CELCAT..."), 0);

    QString url = QString("http://www.edt-sciences.univ-nantes.fr/%1.xml").arg(this->groupId);
    QApplication::setOverrideCursor(Qt::WaitCursor);
    networkManager->get(QNetworkRequest(QUrl(url)));
    qDebug() << "Getting events from CELCAT";
}

void ParserCELCAT::clearCalendar() {
    // nothing to do
    return;
}

void ParserCELCAT::exportEvent(const QString & title,
                         const QString & description,
                         const QString & location,
                         const Time* start,
                         const Time* end) {
    // nothing to do
    return;
}


void ParserCELCAT::parseEvents(QByteArray in) {

    QFile file("g6935.xml");
	QDomDocument doc;
	doc.setContent(in,false);

	QDomElement rootElement = doc.documentElement();
	QDomElement spanElement = rootElement.firstChildElement("span");
	QDomElement event = rootElement.firstChildElement("event");

	Time *timeCursor = new Time(0, 8, 20, 8, 2012);
	while(!event.isNull()) {
		QString celcatWeek = event.firstChildElement("rawweeks").text();
		int weekNumber = 34;
		weekNumber += celcatWeek.indexOf(QChar('Y'), 0, Qt::CaseInsensitive);
		if (weekNumber > 52) {
			weekNumber = weekNumber - 52;
		}
		timeCursor = new Time(0, 8, 20, 8, 2012);
		while(timeCursor->getWeek() != weekNumber) {
			timeCursor->nextDay();
		}

		QString weekDay = event.firstChildElement("day").text();
		int weekDayNumber = weekDay.toInt();
		QString startHour = event.firstChildElement("starttime").text();
		QString endHour = event.firstChildElement("endtime").text();
		QString typeOfCourse = event.firstChildElement("category").text();
		QString courseType;
		if(typeOfCourse.contains("TD")) {
		courseType = "TD";
		}else if(typeOfCourse.contains("CM")) {
		courseType = "CM";
		}else if(typeOfCourse.contains("TP")) {
		courseType = "TP";
		}
		string strCourseType = courseType.toStdString();
		QDomElement resources = event.firstChildElement("resources");
		QString classroom = resources.firstChildElement("room").text();
		string strClassroomName = classroom.toStdString();
		QDomElement module = resources.firstChildElement("module");
		QDomElement moduleItem = module.firstChildElement("item");
		QString moduleName;
		if(!moduleItem.firstChildElement("a").isNull()) {
		moduleName = moduleItem.firstChildElement("a").text();
		}
		else {
		moduleName = moduleItem.text();
		}
		string strModuleName = moduleName.toStdString();
		QDomElement staff = resources.firstChildElement("staff");
		QString professorName = staff.firstChildElement("item").text();
		string strProfessorName = professorName.toStdString();

		ListOfString beginInfos = explode(startHour.toStdString(), ':');
		ListOfString endInfos = explode(endHour.toStdString(), ':');
		for (int i = 0; i < weekDayNumber; i++) {
			timeCursor->nextDay();
		}

		Time *beginDate = new Time(atoi(beginInfos[1].c_str()),
									atoi(beginInfos[0].c_str()),
									timeCursor->getDay(),
									timeCursor->getMonth(),
									timeCursor->getYear());
		Time *endDate = new Time(atoi(endInfos[1].c_str()),
									atoi(endInfos[0].c_str()),
									timeCursor->getDay(),
									timeCursor->getMonth(),
									timeCursor->getYear());
        string title = strCourseType + " " + strModuleName;
        Slot *slot = this->model->createSlot(beginDate, endDate, title, strProfessorName, strClassroomName);

		event = event.nextSiblingElement("event");
    }
    this->controller->getView()->display();
	delete timeCursor;
}

void ParserCELCAT::replyFinished(QNetworkReply * reply)
{
    QApplication::restoreOverrideCursor();
    QByteArray in = reply->readAll();
    //qDebug() << in;
    this->parseEvents(in);

    if(this->controller->getView()->statusbar->currentMessage() == "Getting events from CELCAT...")
        this->controller->getView()->statusbar->clearMessage();
}

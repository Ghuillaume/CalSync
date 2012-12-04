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

void ParserCELCAT::clearCalendar() {
    // nothing to do
    return;
}

void ParserCELCAT::exportEvent(const QString & title,
                         const QString & description,
                         const Time* start,
                         const Time* end) {
    // nothing to do
    return;
}


void ParserCELCAT::parseEvents(QByteArray in) {
    qDebug() << in;
    // /comptes/E094326D/Cours/Master 1/Semestre 1/GL/CalSync/Calendar
    QFile file("g6935.xml.html");
    if (file.open(QFile::ReadOnly)) {
        QDomDocument doc;
        doc.setContent(&file,false);
        file.close();
        	
        QDomElement rootElement = doc.documentElement();
        QDomElement spanElement = rootElement.firstChildElement("span");
        while(!spanElement.isNull()) {
//            QString date = spanElement.attribute("date");
//            QDate formattedDate = QDate::fromString(date,"dd/MM/yyyy");
//            QString celcatWeek = spanElement.firstChildElement("alleventweeks").text();
//            if(formattedDate.isValid()) {
//                this->celcatDateMapping[celcatWeekRepresentation] = formattedDate;
//            }
//            spanElement = spanElement.nextSiblingElement("span");
        }
        QDomElement event = rootElement.firstChildElement("event");
        while(!event.isNull()) {
            QString celcatWeek = event.firstChildElement("rawweeks").text();
            int week = 34;
            int week+= celcatWeek.indexOf(QChar('Y', 0, Qt::CaseInsensitive));
            Time *dateBeginCelcat = new Time(8, 0, 20, 08, 2012);
            Time *newDate = new Time(8, 0, 20, 08, 2012);
            //while()
            
            QDate mappedDate = this->celcatDateMapping[celcatWeek];
            QString weekDay = event.firstChildElement("day").text();
            int weekDayNumber = atoi(weekDay.toStdString().c_str());
            QDate courseDate = mappedDate.addDays(weekDayNumber);
            QString startHour = event.firstChildElement("starttime").text();
            Hour modelBeginHour = Hour(startHour.toStdString());
            QString endHour = event.firstChildElement("endtime").text();
            Hour modelEndHour = Hour(endHour.toStdString());
            QString typeOfCourse = event.firstChildElement("category").text();
            QString courseType;
            if(typeOfCourse.contains("TD")) {
            courseType = "TD";
            }else if(typeOfCourse.contains("CM")) {
            courseType = "CM";
            }else if(typeOfCourse.contains("TP")) {
            courseType = "TP";
            }
            string modelCourseType = courseType.toStdString();
            QDomElement resources = event.firstChildElement("resources");
            QString classroom = resources.firstChildElement("room").text();
            string modelClassroomName = classroom.toStdString();
            QDomElement module = resources.firstChildElement("module");
            QDomElement moduleItem = module.firstChildElement("item");
            QString moduleName;
            if(!moduleItem.firstChildElement("a").isNull()) {
            moduleName = moduleItem.firstChildElement("a").text();
            }
            else {
            moduleName = moduleItem.text();
            }
            string modelModuleName = moduleName.toStdString();
            QDomElement staff = resources.firstChildElement("staff");
            QString professorName = staff.firstChildElement("item").text();
            string modelProfessorName = professorName.toStdString();

            try {
            this->model->addCourse(
            this->modelBeanFactory->createCourse(
            modelCourseType,
            this->modelBeanFactory->createProfessor(modelProfessorName),
            this->modelBeanFactory->createSubject(modelModuleName),
            this->modelBeanFactory->createClassroom(modelClassroomName),
            courseDate,
            modelBeginHour,
            modelEndHour
            )
            );
            }catch(exception& e) {
                std::cout << "exception" << std::endl;
            }

            event = event.nextSiblingElement("event");
        }
        
    }

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

#include "../../headers/Controller/Controller.hpp"

Controller::Controller(Model* model, View* view, Config* config)
{
    this -> model = model;
    this -> view = view;
    this -> config = config;
    
    // Starting view
    QObject::connect(view -> newEmptyModel, SIGNAL(clicked()), this, SLOT(newEmptyModel()));
    QObject::connect(view -> newModelFromLocal, SIGNAL(clicked()), this, SLOT(newModelFromLocal()));
    QObject::connect(view -> newModelFromGoogle, SIGNAL(clicked()), this, SLOT(newModelFromGoogle()));

    // Menubar
    QObject::connect(view -> newItem, SIGNAL(activated()), this, SLOT(setStartView()));
    QObject::connect(view -> saveItem, SIGNAL(activated()), this, SLOT(saveModel()));
    QObject::connect(view -> saveAsItem, SIGNAL(activated()), this, SLOT(saveModelAs()));
    QObject::connect(view -> openItem, SIGNAL(activated()), this, SLOT(loadModel()));
    QObject::connect(view -> quitItem, SIGNAL(activated()), this, SLOT(close()));

    QObject::connect(view -> newSlotItem, SIGNAL(activated()), this, SLOT(createSlot()));
    QObject::connect(view -> tableWidget, SIGNAL(cellDoubleClicked(int,int)), this, SLOT(createSlot()));
    QObject::connect(view -> settingsItem, SIGNAL(activated()), this, SLOT(updateSettings()));
    QObject::connect(view -> reloadItem, SIGNAL(activated()), this, SLOT(newModelFromGoogle()));
    QObject::connect(view -> importItem, SIGNAL(activated()), this, SLOT(importAcademicCalendar()));
    QObject::connect(view -> exportItem, SIGNAL(activated()), this, SLOT(exportCalendar()));
    
    // Main frame
    QObject::connect(view -> datePrevious, SIGNAL(clicked()), this, SLOT(previousWeek()));
    QObject::connect(view -> dateNext, SIGNAL(clicked()), this, SLOT(nextWeek()));

    // Network :
    QObject::connect(this, SIGNAL(tokenSaved()), this, SLOT(askCalendarList()));
    QObject::connect(this, SIGNAL(sendMessage(QString, int)), this->view->statusbar, SLOT(showMessage(QString, int)));

    
}

Controller::~Controller() { }

View* Controller::getView() {
    return this->view;
}


void Controller::newEmptyModel() {
    this->view->menubar->setVisible(true);
    this->view->mainFrame->setVisible(true);
    this->view->horizontalLayoutWidgetNewModel->setVisible(false);
    
    // Clean model and config
    this->model->cleanList();
    this->config->clean();

    if(QMessageBox::question(this, "Password", "Do you want to protect your calendar with a password ?\nYou will be able to modify it in Edit --> Settings menu", QMessageBox::Yes, QMessageBox::No) == QMessageBox::Yes)
        this->changePassword();
    
    this->view->display();
}

void Controller::newModelFromLocal() {
    this->view->menubar->setVisible(true);
    this->view->mainFrame->setVisible(true);
    this->view->horizontalLayoutWidgetNewModel->setVisible(false);
    
    this->loadModel();
    
    this->view->display();
}

void Controller::newModelFromGoogle() {
    if(checkGoogleAuth()) {
        this->view->menubar->setVisible(true);
        this->view->mainFrame->setVisible(true);
        this->view->horizontalLayoutWidgetNewModel->setVisible(false);

        this->importOnlineCalendar();
        
        this->view->display();
    }

}

void Controller::askCalendarList() {

    emit sendMessage(QString("Getting calendar list..."), 0);
    QNetworkAccessManager *networkManager = new QNetworkAccessManager(this);
    QObject::connect(networkManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(selectCalendar(QNetworkReply*)));
    QString url = QString("https://www.googleapis.com/calendar/v3/users/me/calendarList?access_token=%1").arg(this->config->getGoogleAuthCode());
    QApplication::setOverrideCursor(Qt::WaitCursor);
    networkManager->get(QNetworkRequest(QUrl(url)));
}

void Controller::selectCalendar(QNetworkReply* list) {

    if(this->view->statusbar->currentMessage() == "Getting calendar list...")
        this->view->statusbar->clearMessage();

    QJson::Parser parser;
    bool ok = FALSE;

    QVariant result = parser.parse(list->readAll(), &ok).toMap();
    if (!ok) {
      qFatal("An error occurred during parsing calendar list");
    } else {
        if(result.toMap().contains("error"))
        {
            qDebug() << "ERROR occured:\n";
            return;
        }
        else if(result.toMap()["kind"].toString() == "calendar#calendarList")
        {
            this->config->setCalendarList(new QVariantList(result.toMap()["items"].toList()));
        }
    }
    QApplication::restoreOverrideCursor();

    QMessageBox::information(this, "No calendar selected",
                             "Now you are authenticate, please select a calendar in the list, then please retry your request if necessary.");
    this->updateSettings();
    if(this->model->getSlotList().empty())
        this->importOnlineCalendar();
}

void Controller::connectAllSlots() {
    for(unsigned int i = 0; i < this->view->currentButtons.size(); i++) {
		SlotFrame *frame = this->view->currentButtons.at(i);
		QObject::connect(frame, SIGNAL(slotClickedSignal(SlotFrame*)), this, SLOT(clickSlot(SlotFrame*)));
    }
}

void Controller::setStartView() {

    // Checking if current local changes are saved
    bool ok = true;
    switch(this->checkIfSaved()) {
        // Not saved but continue
        case 0:
            ok = true;
            break;

            // Not saved, stop
        case 1:
            ok = false;
            break;

            // Saved, ok
        case 2:
            ok = true;
            break;
    }

    if(ok) {
        this->model->cleanList();
        this->view->menubar->setVisible(false);
        this->view->mainFrame->setVisible(false);
        this->view->horizontalLayoutWidgetNewModel->setVisible(true);
    }
}

void Controller::saveModel() {
    QString fileName = this->config->getFileName();
    qDebug() << "Filename : " << fileName;
    if(!fileName.isEmpty()) {
        qDebug() << "parse with file name";
        this->parseModel(fileName);
    }
    else {
        qDebug() << "Going to ask filename";
        this->saveModelAs();
    }
}

void Controller::saveModelAs() {

    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"), "/home", tr("XML Document (*.xml)"));
    if(!fileName.endsWith(".xml"))
        fileName += ".xml";
    this->config->setFileName(fileName);
    this->parseModel(fileName);
}

void Controller::loadModel() {

    bool load = true;

    if(!this->config->isSaved()) {
        if(QMessageBox::warning(this, "Warning", "Your changes will be lost. Continue without save ?", QMessageBox::Ok, QMessageBox::Cancel) == QMessageBox::Cancel)
            load = false;
    }

    if(load) {
        emit sendMessage("Loading file...", 0);

        QXmlStreamReader reader;
        QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "/home", tr("XML Document (*.xml)"));
        this->config->setFileName(fileName);

        QFile xml_doc(fileName);
        if(!xml_doc.open(QIODevice::ReadOnly))
        {
             QMessageBox::critical(this, "Error", "Failed to open file");
             return;
        }

        reader.setDevice(&xml_doc);

        // If load didn't fail, clean model & config
        this->model->cleanList();
        this->config->clean();
        
        while (!reader.atEnd()) {
            if (reader.isStartElement())
            {
                QString titre;
                QString description;
                QString location;
                QString dateDebut;
                QString dateFin;

                // Si on est à la racine, rien à faire
                if(reader.name() == "Calendar") {
                    reader.readNext();
                }

                // Import du mot de passe et du token d'accès dans la conf
                if(reader.name() == "password") {
                    config->setPassword(reader.readElementText().toStdString());
                }

                if(reader.name() == "googleToken") {
                    config->setGoogleAuthCode(reader.readElementText());
                }

                // On commence à sauvegarder les informations des slots
                if(reader.name() == "slot") {
                    reader.readNext();
                    while(reader.isStartElement()==false) {
                        reader.readNext();
                    }
                }

                if (reader.name() == "title") {
                    titre = reader.readElementText();
                    reader.readNext();
                    while(reader.isStartElement()==false) {
                        reader.readNext();
                    }
                }

                if (reader.name() == "description") {
                    description = reader.readElementText();
                    reader.readNext();
                    while(reader.isStartElement()==false) {
                        reader.readNext();
                    }
                }

                if (reader.name() == "location") {
                    location = reader.readElementText();
                    reader.readNext();
                    while(reader.isStartElement()==false) {
                        reader.readNext();
                    }
                }

                if (reader.name() == "dateStart") {
                    dateDebut = reader.readElementText();
                    reader.readNext();
                    while(reader.isStartElement()==false) {
                        reader.readNext();
                    }
                }

                if (reader.name() == "dateEnd") {
                    dateFin = reader.readElementText();
                }

                // Une fois qu'on a parsé le slot, on crée l'objet correspondant et on l'ajoute au modèle
                if(dateDebut != NULL && dateFin != NULL) {
                    model->createSlot( createTime(dateDebut),
                    createTime(dateFin),
                    titre.toStdString(),
                    description.toStdString(),
                    location.toStdString());
                }
            }
            reader.readNext(); // On va au prochain token
        }

        // On ferme le flux et on rafraichit l'interface
        xml_doc.close();
        this->view->display();

        if(this->view->statusbar->currentMessage() == "Loading file...")
            this->view->statusbar->clearMessage();
    }

}

void Controller::close() {
    switch(this->checkIfSaved()) {

        // Not saved but continue
        case 0:
            this->view->close();
            break;

            // Not saved and stop exiting
        case 1:
            break;

            // Saved, ok
        case 2:
            if(QMessageBox::question(this, "Warning", "Are you sure ?", QMessageBox::Ok, QMessageBox::Cancel) == QMessageBox::Ok) {
                this->view->close();
            }
            break;
    }
}

void Controller::createSlot()
{
    SlotDialog *dialog = new SlotDialog(view);
    QObject::connect(dialog, SIGNAL(acceptedAndOk()), dialog, SLOT(accept()));
    QObject::connect(dialog->buttonBox, SIGNAL(rejected()), dialog, SLOT(reject()));
    dialog -> exec();

    if(dialog->result() == QDialog::Accepted) {
        QDate startDate = dialog->dateStartEdit->date();
        QTime startTime = dialog->dateStartEdit->time();
        QDate endDate = dialog->dateEndEdit->date();
        QTime endTime = dialog->dateEndEdit->time();

        Time *startDateTime = new Time(startTime.minute(), startTime.hour(), startDate.day(), startDate.month(), startDate.year());
        Time *endDateTime = new Time(endTime.minute(), endTime.hour(), endDate.day(), endDate.month(), endDate.year());

        if(*startDateTime > *endDateTime) {
            QMessageBox::critical(this->view, "Error", "You can't create an event which end before starting!\n Creation aborted");
        } else if (startDateTime->getDay() != endDateTime->getDay()
					|| startDateTime->getMonth() != endDateTime->getMonth()
					|| startDateTime->getYear() != endDateTime->getYear()) {
            QMessageBox::critical(this->view, "Error", "The date of the beginning of the event must be the same for the end!\n Creation aborted");
		} else {

            if(this->checkConflicts(startDateTime, endDateTime, NULL)) {

                this->config->setSaved(false);
                this->model->createSlot(startDateTime,
                                        endDateTime,
                                        dialog->titleEdit->text().toStdString(),
                                        dialog->descriptionEdit->text().toStdString(),
                                        dialog->locationEdit->text().toStdString());


                this->view->display();
                this->connectAllSlots();
            }
		}
    }
}

void Controller::editSlot(SlotFrame *frame) {
	SlotDialog *dialog = new SlotDialog(view);
	QObject::connect(dialog->buttonBox, SIGNAL(accepted()), dialog, SLOT(accept()));
	QObject::connect(dialog->buttonBox, SIGNAL(rejected()), dialog, SLOT(reject()));
	
    dialog->setArgs(frame->getSlot()->getDateDebut(), frame->getSlot()->getDateFin(),
                    frame->getSlot()->getIntitule(), frame->getSlot()->getDescription());
    dialog -> exec();
	if(dialog->result() == QDialog::Accepted) {
		QDate startDate = dialog->dateStartEdit->date();
		QTime startTime = dialog->dateStartEdit->time();
		QDate endDate = dialog->dateEndEdit->date();
		QTime endTime = dialog->dateEndEdit->time();

		Time* startDateTime = new Time(startTime.minute(), startTime.hour(), startDate.day(), startDate.month(), startDate.year());
		Time* endDateTime = new Time(endTime.minute(), endTime.hour(), endDate.day(), endDate.month(), endDate.year());

		if(*startDateTime > *endDateTime) {
			QMessageBox::critical(this->view, "Error", "You can't create an event which ends before starting ! Edition aborted.");
			return;
		}

        if(this->checkConflicts(startDateTime, endDateTime, frame->getSlot())) {

            this->config->setSaved(false);
            frame->getSlot()->editSlot( startDateTime,
                                        endDateTime,
                                        dialog->titleEdit->text().toStdString(),
                                        dialog->descriptionEdit->text().toStdString());
            this->view->display();
            this->connectAllSlots();
        }
	}
}

void Controller::deleteSlot(SlotFrame *frame) {
	QString warning = "Are you sure you want to delete the event \"" + QString(frame->getSlot()->getIntitule().c_str()) + "\" ?";
	if(QMessageBox::warning(this, "Warning", warning, QMessageBox::Ok, QMessageBox::Cancel) == QMessageBox::Ok) {
		this->model->deleteSlot(frame->getSlot());
		this->view->display();
		this->connectAllSlots();
	}

	this->config->setSaved(false);
}

void Controller::updateSettings() {

    SettingsDialog* dialog = new SettingsDialog(view);
    QObject::connect(dialog->buttonBox, SIGNAL(accepted()), dialog, SLOT(accept()));
    QObject::connect(dialog->buttonBox, SIGNAL(rejected()), dialog, SLOT(reject()));
    QObject::connect(dialog->pwdButton, SIGNAL(clicked()), this, SLOT(changePassword()));
    QObject::connect(dialog->serviceBox, SIGNAL(currentIndexChanged(QString)), this, SLOT(updateOnlineService(QString)));
    QObject::connect(dialog->inputCalendarBox, SIGNAL(currentIndexChanged(QString)), this, SLOT(updateAcademicSchedule(QString)));
    QObject::connect(dialog->idCalendarBox, SIGNAL(currentIndexChanged(int)), this, SLOT(updateGCalID(int)));
    QObject::connect(dialog->googleAuthButton, SIGNAL(clicked()), this, SLOT(getGoogleAccessToken()));
    QObject::connect(dialog->googleAuthButton, SIGNAL(clicked()), dialog, SLOT(reject()));
    dialog->setCalendarList(this->config->getCalendarList(), this->config->getGCalId());
    dialog->groupEdit->setText(this->config->getCelcatGroup());
    dialog -> exec();
    this->config->setCelcatGroup(dialog->groupEdit->text());
}

void Controller::updateGCalID(int i) {
    QVariantMap calendar = this->config->getCalendarList()->at(i).toMap();
    this->config->setGCalId(calendar["id"].toString());
    qDebug() << "New GCal ID is " << this->config->getGCalId();
}

void Controller::updateOnlineService(QString service) {
    this->config->setOnlineService(service.toStdString());
    this->view->exportItem->setText(QString("Save my calendar on %1").arg(service));
    this->view->reloadItem->setText(QString("Save my calendar on %1").arg(service));
}

void Controller::updateAcademicSchedule(QString schedule) {
    this->config->setAcademicSchedule(schedule.toStdString());
    this->view->importItem->setText(QString("Update local calendar from %1").arg(schedule));
}

void Controller::parseModel(QString fileName) {

    emit sendMessage(QString("Saving events locally..."), 0);

    bool pwdOK = false;
    if(this->config->getPassword().empty())
        pwdOK = true;
    else {
        QString passwdChecking = QInputDialog::getText(this, "Password", "Type your password");
        if(md5(passwdChecking.toStdString()) == this->config->getPassword()) {
            pwdOK = true;
        }
    }
    
    if(!pwdOK) {
        QMessageBox::warning(this, "Warning", "Wrong password");
    }
    else {
        // Création de l'arbre DOM
        QDomDocument dom("dom");
        QFile xml_doc(fileName);
        QDomElement rootNode = dom.createElement("Calendar");
        dom.appendChild(rootNode);
        QDomElement passwd = dom.createElement("password");
        passwd.appendChild(dom.createTextNode(this->config->getPassword().c_str()));
        rootNode.appendChild(passwd);
        QDomElement token = dom.createElement("googleToken");
        token.appendChild(dom.createTextNode(this->config->getGoogleAuthCode()));
        rootNode.appendChild(token);

        ListOfSlot l = this->model->getSlotList();
        QDomElement slotlistXML = dom.createElement("slotlist");
        rootNode.appendChild(slotlistXML);
        for(ListOfSlot::iterator it = l.begin() ; it != l.end() ; it++) {
            QDomElement slotXML = dom.createElement("slot");
            slotlistXML.appendChild(slotXML);

            QDomElement titreXML = dom.createElement("title");
            titreXML.appendChild(dom.createTextNode((*it)->getIntitule().c_str()));
            slotXML.appendChild(titreXML);
            QDomElement descriptionXML = dom.createElement("description");
            descriptionXML.appendChild(dom.createTextNode((*it)->getDescription().c_str()));
            slotXML.appendChild(descriptionXML);
            QDomElement locationXML = dom.createElement("location");
            locationXML.appendChild(dom.createTextNode((*it)->getLocation().c_str()));
            slotXML.appendChild(locationXML);

            QDomElement dateStartXML = dom.createElement("dateStart");
            dateStartXML.appendChild(dom.createTextNode((*it)->getDateDebut()->getXmlDate().c_str()));
            slotXML.appendChild(dateStartXML);

            QDomElement dateEndXML = dom.createElement("dateEnd");
            dateEndXML.appendChild(dom.createTextNode((*it)->getDateFin()->getXmlDate().c_str()));
            slotXML.appendChild(dateEndXML);
        }

        // Écriture de l'arbre DOM dans fichier XML
        xml_doc.open(QIODevice::WriteOnly);
        QTextStream ts(&xml_doc);
        ts << dom.toString();
        xml_doc.close();


        this->config->setSaved(true);
    }
    if(this->view->statusbar->currentMessage() == "Saving events locally...")
        this->view->statusbar->clearMessage();
    
}

void Controller::previousWeek() {
    this->view->previousWeek();
    this->connectAllSlots();
}

void Controller::nextWeek() {
    this->view->nextWeek();
    this->connectAllSlots();
}

bool Controller::checkConflicts(Time* start, Time* end, Slot* currentSlot) {
    bool proceed = true;
    bool overlap = true;
    ListOfSlot list;
    while(overlap) {
        overlap = false;
        list = this->model->getSlotList();
        for(ListOfSlot::iterator it = list.begin(); it != list.end() ; it++) {
            if((*it)->areSlotsOverlapping(start, end) && (currentSlot != (*it))) {
                // Overlapping, ask user for resolving conflict
                QString event = (*it)->getIntitule().c_str();
                QString message = "Your new event overlaps event \"" + event + "\" and will erase it";
                if(QMessageBox::question(this, "Conflict", message, QMessageBox::Abort, QMessageBox::Apply) == QMessageBox::Apply) {
                    qDebug() << "erase" << endl;
                    this->config->setSaved(false);
                    this->model->deleteSlot(*it);
                    overlap = true;
                    break;
                }
                else {
                    qDebug() << "discard" << endl;
                    proceed = false;
                }
            }
        }
    }

    return proceed;
}

int Controller::checkIfSaved() {

    if(!this->config->isSaved()) {
        if(QMessageBox::warning(this, "Warning", "You didn't save your changes neither localy nor online. Continue ?", QMessageBox::Ok, QMessageBox::Cancel) == QMessageBox::Cancel) {
            return 1;
        }
        else {
            return 0;
        }
    }
    else
        return 2;

}

bool Controller::checkGoogleAuth() {
    bool ok = false;
    if(this->config->getGoogleAuthCode().isEmpty()) {
        if(QMessageBox::warning(this, "Warning", "You are not authenticated, click OK if you want to launch authentication", QMessageBox::Ok, QMessageBox::Abort) == QMessageBox::Abort) {
            ok = false;
        }
        else {
            ok = true;
            this->getGoogleAccessToken();
        }
    }
    else {
        ok = true;

        if(QMessageBox::warning(this, "Warning", "You are already authenticated, do you want to authenticate with another account ?", QMessageBox::Yes, QMessageBox::No) == QMessageBox::Yes) {
            this->getGoogleAccessToken();
        }
    }
    
    return ok;
}

void Controller::changePassword() {
    if(!this->config->getPassword().empty()) {
        QString passwdChecking = QInputDialog::getText(this, "Password", "Type your current password");
        if(md5(passwdChecking.toStdString()) != this->config->getPassword()) {
            QMessageBox::warning(this, "Warning", "Wrong password");
            return;
        }
    }

    QString passwd = QInputDialog::getText(this, "Password", "Type new password");

    this->config->setPassword(md5(passwd.toStdString()));
}

void Controller::getGoogleAccessToken() {
    this->auth2 = new OAuth2(this);
    this->auth2->startLogin(false);

    this->connect(this->auth2,SIGNAL(sigCodeObtained(QString)),this,SLOT(googleCodeObtained(QString)));

}

void Controller::googleCodeObtained(QString authCode) {
    qDebug() << "Google code obtained : " << authCode;
    this->auth2->askTokenAccess(authCode);
    QObject::connect(this->auth2, SIGNAL(tokenObtained(QString)), this, SLOT(googleAccessTokenObtained(QString)));
}

void Controller::googleAccessTokenObtained(QString token) {
    qDebug() << "Google token obtained : " << token;
    this->config->setGoogleOAuth(this->auth2);
    this->config->setGoogleAuthCode(token);
    emit tokenSaved();
}

void Controller::importAcademicCalendar() {

    Parser* p = new ParserCELCAT(this->config->getCelcatGroup(), this->model, this, this);
    p->getEventList();
}


void Controller::importOnlineCalendar() {

    this->model->cleanList();

    // create Google Parser and parse
    Parser* p = new ParserGCal(this->config->getGCalId(), this->config->getGoogleAuthCode(), this->model, this, this);
    p->getEventList();
}

void Controller::exportCalendar() {
    if(checkGoogleAuth()) {
        if(QMessageBox::warning(this->view, "Warning", "This action is going to clear your online Calendar before, do you want to continue ?", QMessageBox::Yes, QMessageBox::No) == QMessageBox::Yes) {
            Parser* p = new ParserGCal(this->config->getGCalId(), this->config->getGoogleAuthCode(), this->model, this, this);
            p->clearCalendar();

            ListOfSlot list = this->model->getSlotList();
            for(ListOfSlot::iterator it = list.begin(); it != list.end() ; it++) {
                p->exportEvent(QString((*it)->getIntitule().c_str()), QString((*it)->getDescription().c_str()), QString((*it)->getLocation().c_str()), (*it)->getDateDebut(), (*it)->getDateFin());
            }
        }
    }
}

Time* Controller::createTime(const QString &chaine) {

	ListOfString chaineHeure = explode(chaine.toStdString(), ':');
	ListOfString chaineDate = explode(chaineHeure[2], '/');
	int heure = QString(chaineHeure[0].c_str()).toInt();
	int minute = QString(chaineHeure[1].c_str()).toInt();
	int jour = QString(chaineDate[0].c_str()).toInt();
	int mois = QString(chaineDate[1].c_str()).toInt();
	int annee = QString(chaineDate[2].c_str()).toInt();

	return new Time(minute, heure, jour, mois, annee);
}

void Controller::clickSlot(SlotFrame *frame) {
	SlotActionDialog *slotActionDialog = new SlotActionDialog(view, frame);
    slotActionDialog->setVisible(true);
        
    QObject::connect(slotActionDialog->editionButton, SIGNAL(clicked()), slotActionDialog, SLOT(editSlot()));
    QObject::connect(slotActionDialog, SIGNAL(editSlotSignal(SlotFrame*)), this, SLOT(editSlot(SlotFrame*)));
    QObject::connect(slotActionDialog->deletionButton, SIGNAL(clicked()), slotActionDialog, SLOT(deleteSlot()));
    QObject::connect(slotActionDialog, SIGNAL(deleteSlotSignal(SlotFrame*)), this, SLOT(deleteSlot(SlotFrame*)));
    QObject::connect(slotActionDialog->cancelButton, SIGNAL(clicked()), slotActionDialog, SLOT(close()));
}

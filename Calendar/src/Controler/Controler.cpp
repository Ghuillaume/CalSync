#include "../../headers/Controler/Controler.hpp"

#include <qt4/QtXml/QtXml>
#include <qt4/QtXml/QDomDocument>

Controler::Controler(Model* model, View* view, Config* config)
{
    this -> model = model;
    this -> view = view;
    this -> config = config;
    
    
    // Menubar
    QObject::connect(view -> newItem, SIGNAL(activated()), this, SLOT(setStartView()));
    QObject::connect(view -> saveAsItem, SIGNAL(activated()), this, SLOT(saveModel()));
    QObject::connect(view -> openItem, SIGNAL(activated()), this, SLOT(loadModel()));
    QObject::connect(view -> quitItem, SIGNAL(activated()), this, SLOT(close()));
    
    QObject::connect(view -> newSlotItem, SIGNAL(activated()), this, SLOT(createSlot()));
    QObject::connect(view -> editSlotItem, SIGNAL(activated()), this, SLOT(editSlot()));
    QObject::connect(view -> deleteSlotItem, SIGNAL(activated()), this, SLOT(deleteSlot()));
    QObject::connect(view -> changePwdItem, SIGNAL(activated()), this, SLOT(changePassword()));
    QObject::connect(view -> changeKeyItem, SIGNAL(activated()), this, SLOT(changeAPIKey()));
    
    
    // Main frame
    QObject::connect(view -> datePrevious, SIGNAL(clicked()), view, SLOT(previousWeek()));
    QObject::connect(view -> dateNext, SIGNAL(clicked()), view, SLOT(nextWeek()));
    
    QObject::connect(view -> newEmptyModel, SIGNAL(clicked()), this, SLOT(newEmptyModel()));
    QObject::connect(view -> newModelFromLocal, SIGNAL(clicked()), this, SLOT(newModelFromLocal()));
    QObject::connect(view -> newModelFromGoogle, SIGNAL(clicked()), this, SLOT(newModelFromGoogle()));
    
}

Controler::~Controler() { }


void Controler::setStartView() {
    
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
        this->view->menubar->setVisible(false);
        this->view->mainFrame->setVisible(false);
        this->view->horizontalLayoutWidgetNewModel->setVisible(true);
    }
}

void Controler::newEmptyModel() {
    this->view->menubar->setVisible(true);
    this->view->mainFrame->setVisible(true);
    this->view->horizontalLayoutWidgetNewModel->setVisible(false);

    if(QMessageBox::question(this, "Password", "Do you want to protect your calendar with a password ?", QMessageBox::Yes, QMessageBox::No) == QMessageBox::Yes)
        this->changePassword();
}

void Controler::newModelFromLocal() {
    this->view->menubar->setVisible(true);
    this->view->mainFrame->setVisible(true);
    this->view->horizontalLayoutWidgetNewModel->setVisible(false);
    
    this->loadModel();
}

void Controler::newModelFromGoogle() {
    this->view->menubar->setVisible(true);
    this->view->mainFrame->setVisible(true);
    this->view->horizontalLayoutWidgetNewModel->setVisible(false);

    // Todo : verif if it's needed to change API key. Idem for GCal id
    string gcalID = "k2k3gliju4hpiptoaa1cprn6f8%40group.calendar.google.com";
    string apiKey = "AIzaSyDNTR8D9cS5lQOqVW5dX1dFpKgQqlKA9sM";

    // create Google Parser and parse
    // Todo : ask for password
    Parser* p = new ParserGCal("www.googleapis.com", true, gcalID, apiKey, this->model, this);
    p->getEventList();

}

void Controler::selectWeek()
{
	DateDialog *dialog = new DateDialog(view);
	QObject::connect(dialog->buttonBox, SIGNAL(accepted()), dialog, SLOT(setWeek()));
	QObject::connect(dialog->buttonBox, SIGNAL(rejected()), dialog, SLOT(reject()));
	dialog -> exec();
	delete dialog;
	view -> display ();
}

void Controler::createSlot()
{
    SlotDialog *dialog = new SlotDialog(view);
    QObject::connect(dialog->buttonBox, SIGNAL(accepted()), dialog, SLOT(accept()));
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
            QMessageBox::critical(this->view, "Error", "You can't create an event which end before starting ! Creation aborted");
            return;
        }
        
        // Checking conflicts
        bool overlap = true;
        ListOfSlot list;
        while(overlap) {
            overlap = false;
            list = this->model->getSlotList();
            for(ListOfSlot::iterator it = list.begin();  it != list.end() ; it++) {
                if((*it)->areSlotsOverlapping(startDateTime, endDateTime)) {
                    // Overlapping, ask user for resolving conflict
                    QString event = (*it)->getIntitule().c_str();
                    QString message = "Your new event overlaps event \"" + event + "\" and will erase it";
                    if(QMessageBox::question(this, "Conflict", message, QMessageBox::Discard, QMessageBox::Apply) == QMessageBox::Apply) {
                        qDebug() << "erase" << endl;
                        this->config->setSaved(false);
                        this->model->deleteSlot(*it);
                        overlap = true;
                        break;
                    }
                    else {
                        qDebug() << "discard" << endl;
                        return;
                    }
                }
            }
        }

        this->config->setSaved(false);
        this->model->createSlot(startDateTime,
                                endDateTime,
                                dialog->titleEdit->text().toStdString(),
                                dialog->descriptionEdit->text().toStdString());

        this->view->display();
    }
}

void Controler::editSlot() {
    if(this->view->slotListWidget->currentRow() == -1)
        QMessageBox::warning(this, "Error", "You must select an event in the list before edit it.");
    else {

        // Récupération de l'élement à modifier
        ListOfSlot l = this->model->getSlotList();
        ListOfSlot::iterator slotToEditIterator;
        int cpt = 0;
        for(slotToEditIterator = l.begin() ;
            slotToEditIterator != l.end() && cpt < (this->view->getFirstEventPosition() + this->view->slotListWidget->currentRow()) ;
            slotToEditIterator++)
        {
            cpt++;
        }

        SlotDialog *dialog = new SlotDialog(view);
        QObject::connect(dialog->buttonBox, SIGNAL(accepted()), dialog, SLOT(accept()));
        QObject::connect(dialog->buttonBox, SIGNAL(rejected()), dialog, SLOT(reject()));
        dialog->setArgs((*slotToEditIterator)->getDateDebut(), (*slotToEditIterator)->getDateFin(), (*slotToEditIterator)->getIntitule(), (*slotToEditIterator)->getDescription());
        dialog -> exec();
        if(dialog->result() == QDialog::Accepted) {
            view -> display ();
            QDate startDate = dialog->dateStartEdit->date();
            QTime startTime = dialog->dateStartEdit->time();
            QDate endDate = dialog->dateEndEdit->date();
            QTime endTime = dialog->dateEndEdit->time();

            Time* startDateTime = new Time(startTime.minute(), startTime.hour(), startDate.day(), startDate.month(), startDate.year());
            Time* endDateTime = new Time(endTime.minute(), endTime.hour(), endDate.day(), endDate.month(), endDate.year());
            
            if(*startDateTime > *endDateTime) {
                QMessageBox::critical(this->view, "Error", "You can't create an event which end before starting ! Edition aborted.");
                return;
            }
            
            // Checking conflicts
            bool overlap = true;
            ListOfSlot list;
            while(overlap) {
                overlap = false;
                list = this->model->getSlotList();
                for(ListOfSlot::iterator it = list.begin();  it != list.end(); it++) {
                    if((*it)->areSlotsOverlapping(startDateTime, endDateTime) && ((*slotToEditIterator) != (*it))) {
                        qDebug() << (*slotToEditIterator)->toString().c_str() << " & " << (*it)->toString().c_str() << "overlaped";
                        // Overlapping, ask user for resolving conflict
                        QString event = (*it)->getIntitule().c_str();
                        QString message = "Your new event overlaps event \"" + event + "\" and will erase it";
                        if(QMessageBox::question(this, "Conflict", message, QMessageBox::Discard, QMessageBox::Apply) == QMessageBox::Apply) {
                            qDebug() << "erase" << endl;
                            this->config->setSaved(false);
                            this->model->deleteSlot(*it);
                            overlap = true;
                            break;
                        }
                        else {
                            qDebug() << "discard" << endl;
                            return;
                        }
                    }
                }
            }

            this->config->setSaved(false);
            (*slotToEditIterator)->editSlot(
                        startDateTime,
                        endDateTime,
                        dialog->titleEdit->text().toStdString(),
                        dialog->descriptionEdit->text().toStdString());
            this->view->display();
        }

    }
}

void Controler::deleteSlot() {
    if(this->view->slotListWidget->currentRow() == -1)
        QMessageBox::warning(this, "Error", "You must select an event in the list before delete it.");
    else {

        // Récupération de l'élément à supprimer
        ListOfSlot l = this->model->getSlotList();
        ListOfSlot::iterator slotToDelIterator;
        int cpt = 0;
        for(slotToDelIterator = l.begin() ;
            slotToDelIterator != l.end() && cpt < (this->view->getFirstEventPosition() + this->view->slotListWidget->currentRow()) ;
            slotToDelIterator++)
        {
            cpt++;
        }

        QString warning = "Are you sure you want to delete the event \"" + QString((*slotToDelIterator)->getIntitule().c_str()) + "\" ?";
        if(QMessageBox::warning(this, "Warning", warning, QMessageBox::Ok, QMessageBox::Cancel) == QMessageBox::Ok) {
            this->model->deleteSlot(*slotToDelIterator);
            this->view->display();
        }

        this->config->setSaved(false);

    }

}

void Controler::saveModel() {

    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"), "/home", tr("XML Document (*.xml)"));

    // Création de l'arbre DOM
    QDomDocument dom("dom");
    QFile xml_doc(fileName);
    QDomElement rootNode = dom.createElement("Calendar");
    dom.appendChild(rootNode);
    QDomElement passwd = dom.createElement("password");
    passwd.appendChild(dom.createTextNode(this->config->getPassword().c_str()));
    rootNode.appendChild(passwd);
    QDomElement apikey = dom.createElement("apikey");
    apikey.appendChild(dom.createTextNode(this->config->getAPIKEY().c_str()));
    rootNode.appendChild(apikey);

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

        QDomElement dateStartXML = dom.createElement("dateStart");
        dateStartXML.appendChild(dom.createTextNode((*it)->getDateDebut()->getDate().c_str()));
        slotXML.appendChild(dateStartXML);

        QDomElement dateEndXML = dom.createElement("dateEnd");
        dateEndXML.appendChild(dom.createTextNode((*it)->getDateFin()->getDate().c_str()));
        slotXML.appendChild(dateEndXML);
    }

    // Écriture de l'arbre DOM dans fichier XML
    xml_doc.open(QIODevice::WriteOnly);
    QTextStream ts(&xml_doc);
    ts << dom.toString();
    xml_doc.close();


    this->config->setSaved(true);
    
}

void Controler::loadModel() {

    // TODO : fonctionne pas bordel de merde !
    // FUCK LA TASSE DE CAFÉ
    // Y A PLUS DE CAFÉ JSUIS DANS LA MAYRDE !!!!



    // LOL

    bool load = true;

    if(!this->config->isSaved()) {
        if(QMessageBox::warning(this, "Warning", "Your changes will be lost. Continue without save ?", QMessageBox::Ok, QMessageBox::Cancel) == QMessageBox::Cancel)
            load = false;
    }

    if(load) {
        QXmlStreamReader reader;
        QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "/home", tr("XML Document (*.xml)"));

        QFile xml_doc(fileName);
        if(!xml_doc.open(QIODevice::ReadOnly))
        {
             QMessageBox::critical(this, "Error", "Failed to open file");
             return;
        }

        reader.setDevice(&xml_doc);

        while (!reader.atEnd()) {
            if (reader.isStartElement())
            {
                if(reader.name() == "Calendar") {

                    reader.readNext();
                    while(reader.isStartElement() == false)
                       reader.readNext();

                    if(reader.name() == "password") {
                        config->setPassword(reader.readElementText().toStdString());
                    }

                    if(reader.name() == "apikey") {
                        config->setAPIKEY(reader.readElementText().toStdString());
                    }
                }
            }
            reader.readNext(); // On va au prochain token
        }

        xml_doc.close();

        this->view->display();
    }

}

void Controler::close() {
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
int Controler::checkIfSaved() {

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


void Controler::changePassword() {
    if(this->config->getPassword().compare("0")) {
        QString passwdChecking = QInputDialog::getText(this, "Password", "Type your current password");
        if(md5(passwdChecking.toStdString()) != this->config->getPassword()) {
            QMessageBox::warning(this, "Warning", "Wrong password");
            return;
        }
    }

    // TODO vérification du passwd ?
    QString passwd = QInputDialog::getText(this, "Password", "Type new password");

    this->config->setPassword(md5(passwd.toStdString()));
}


void Controler::changeAPIKey() {
    QInputDialog askingKey(this);
    askingKey.setLabelText("API Key");
    askingKey.setTextValue(this->config->getAPIKEY().c_str());
    askingKey.exec();

    this->config->setAPIKEY(askingKey.textValue().toStdString());
}

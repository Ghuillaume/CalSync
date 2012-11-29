#include "../../headers/Controler/Controler.hpp"

#include <qt4/QtXml/QtXml>
#include <qt4/QtXml/QDomDocument>

Controler::Controler(Model* model, View* view, Config* config)
{
    this -> model = model;
    this -> view = view;
    this -> config = config;
    
    QObject::connect(view -> newEmptyModel, SIGNAL(clicked()), this, SLOT(newEmptyModel()));
    QObject::connect(view -> newModelFromLocal, SIGNAL(clicked()), this, SLOT(newModelFromLocal()));
    QObject::connect(view -> newModelFromGoogle, SIGNAL(clicked()), this, SLOT(newModelFromGoogle()));
    
}

Controler::~Controler() { }

void Controler::setMainFrameConnections() {
    
    // Connexion signaux/slots de la vue
    QObject::connect(view -> saveAsItem, SIGNAL(activated()), this, SLOT(saveModel()));
    QObject::connect(view -> openItem, SIGNAL(activated()), this, SLOT(loadModel()));
    QObject::connect(view -> quitItem, SIGNAL(activated()), this, SLOT(checkIfSaved()));
    
    QObject::connect(view -> newSlotItem, SIGNAL(activated()), this, SLOT(createSlot()));
    QObject::connect(view -> editSlotItem, SIGNAL(activated()), this, SLOT(editSlot()));
    QObject::connect(view -> deleteSlotItem, SIGNAL(activated()), this, SLOT(deleteSlot()));
    QObject::connect(view -> changePwdItem, SIGNAL(activated()), this, SLOT(changePassword()));
    QObject::connect(view -> changeKeyItem, SIGNAL(activated()), this, SLOT(changeAPIKey()));
    
    QObject::connect(view -> datePrevious, SIGNAL(clicked()), view, SLOT(previousWeek()));
    QObject::connect(view -> dateNext, SIGNAL(clicked()), view, SLOT(nextWeek()));
}

// Public slots :

void Controler::newEmptyModel() {
    this->view->setMainFrame();
    this->setMainFrameConnections();
    delete this->view->horizontalLayoutWidgetNewModel;
    
    if(QMessageBox::question(this, "Password", "Do you want to protect your calendar with a password ?", QMessageBox::Yes, QMessageBox::No) == QMessageBox::Yes)
        this->changePassword();
}

void Controler::newModelFromLocal() {
    this->view->setMainFrame();
    this->loadModel();
    this->setMainFrameConnections();
    delete this->view->horizontalLayoutWidgetNewModel;
}

void Controler::newModelFromGoogle() {
    QMessageBox::critical(this, "LOL", "TODO");
    //delete this->view->horizontalLayoutWidgetNewModel;
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

        switch(this->model->createSlot(startDateTime,
                                    endDateTime,
                                    dialog->titleEdit->text().toStdString(),
                                    dialog->descriptionEdit->text().toStdString()))
        {
            case 0:
                //ok
                this->config->setSaved(false);
                break;
            case 2:
                // slot already inserted
                qWarning() << "Trying to insert a slot which is already in the list";
                break;
            case 1:
                // slot overlaps another slot, ask user if he wants to erase existing slot or keep it
                QString message = "Event blabla overlap event bloublou and will erase it";
                if(QMessageBox::question(this, "Conflict", message, QMessageBox::Discard, QMessageBox::Apply) == QMessageBox::Apply) {
                    qDebug() << "erase" << endl;
                }
                else
                    qDebug() << "discard" << endl;
                break;
        }

        this->view->display ();
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

            (*slotToEditIterator)->editSlot(
                        startDateTime,
                        endDateTime,
                        dialog->titleEdit->text().toStdString(),
                        dialog->descriptionEdit->text().toStdString());
            this->view->display();
        }

        this->config->setSaved(false);
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

void Controler::checkIfSaved() {

    if(!this->config->isSaved()) {
        if(QMessageBox::warning(this, "Warning", "You didn't save your changes neither localy nor online. Continue ?", QMessageBox::Ok, QMessageBox::Cancel) == QMessageBox::Cancel) {
            return;
        }
        else {
            this->view->close();
            return;
        }
    }

    if(QMessageBox::question(this, "Warning", "Are you sure ?", QMessageBox::Ok, QMessageBox::Cancel) == QMessageBox::Ok) {
        this->view->close();
    }
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

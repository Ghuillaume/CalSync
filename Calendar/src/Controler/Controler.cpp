#include "../../headers/Controler/Controler.hpp"
// Public :

Controler::Controler(Model *model, View *view)
{
    this -> model = model;
    this -> view = view;
    
    // Connexion signaux/slots de la vue
    QObject::connect(view -> saveAsItem, SIGNAL(activated()), this, SLOT(saveModel()));
    QObject::connect(view -> quitItem, SIGNAL(activated()), view, SLOT(close()));
    
    QObject::connect(view -> newSlotItem, SIGNAL(activated()), this, SLOT(createSlot()));
    QObject::connect(view -> editSlotItem, SIGNAL(activated()), this, SLOT(editSlot()));
    QObject::connect(view -> deleteSlotItem, SIGNAL(activated()), this, SLOT(deleteSlot()));

	QObject::connect(view -> datePrevious, SIGNAL(clicked()), view, SLOT(previousWeek()));
    QObject::connect(view -> dateNext, SIGNAL(clicked()), view, SLOT(nextWeek()));
	
	//QObject::connect(view -> tableWidget, SIGNAL(cellDoubleClicked(int,int)), this, SLOT(createSlot(int,int)));
}

Controler::~Controler() { }

// Public slots :

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
    QObject::connect(dialog->buttonBox, SIGNAL(accepted()), dialog, SLOT(createSlot()));
    QObject::connect(dialog->buttonBox, SIGNAL(rejected()), dialog, SLOT(reject()));
    dialog -> exec();
    view -> display ();
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

            (*slotToEditIterator)->editSlot(
                        new Time(startTime.minute(), startTime.hour(), startDate.day(), startDate.month(), startDate.year()),
                        new Time(endTime.minute(), endTime.hour(), endDate.day(), endDate.month(), endDate.year()),
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
            this->model->deleteSlot(slotToDelIterator);
            this->view->display();
        }

    }

}

void Controler::saveModel() {
    QMessageBox::warning(this, "TODO", "TODO");
    QString fileName = QFileDialog::getSaveFileName(this, tr("Open File"), "/home", tr("Images (*.xml)"));
    
}
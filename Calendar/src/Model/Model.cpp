/* 
 * File:   Model.cpp
 * Author: e094326d
 * 
 * Created on 18 novembre 2012, 11:44
 */

#include <qt4/QtCore/qglobal.h>

#include "../../headers/Model/Model.hpp"


Model::Model() {
    Time *currentTime = new Time();
    this->currentDate = new Time(0, 8, currentTime->getDay()-currentTime->getWeekDay(), currentTime->getMonth(), currentTime->getYear());    
}

Model::~Model() {
}

ListOfSlot Model::getSlotList() {
    return this->slotlist;
}

Time* Model::getCurrentDate() {
    return this->currentDate;
}

void Model::nextWeek() {
    for (unsigned int i = 0 ; i < 7 ; i++)
        this->currentDate->nextDay();
}
void Model::previousWeek() {
    for (unsigned int i = 0 ; i < 7 ; i++)
        this->currentDate->previousDay();
}

int Model::createSlot(Time *dateDeb, Time *dateFin, string intitule, string description) {
    Slot *newSlot = new Slot(dateDeb, dateFin, intitule, description);

    cout << "inserting slot : " << newSlot->toString() << endl;
    
<<<<<<< HEAD
    int code = 0;
    bool overlap = false;
    for(ListOfSlot::iterator it = this->slotlist.begin();  it != this->slotlist.end(); it++) {
        qDebug() << (*it)->toString().c_str();
        overlap |= (*it)->areSlotsOverlapping(newSlot);
    }

    if (overlap) {
        delete newSlot;
        code = 1;
    } else {
        this->slotlist.insert(newSlot);
    }
=======
>>>>>>> c623c2ec8d60c2a9916e1820505f8cec653d2158
    
    this->slotlist.insert(newSlot);
    
    return 1;

}

void Model::deleteSlot(ListOfSlot::iterator it) {
<<<<<<< HEAD
    cout << "erasing slot : " << (*it)->toString() << endl;
    this->slotlist.erase(*it);
=======
    cout << "erasing slot from iterator : " << (*it)->toString() << endl;
    this->slotlist.erase(it);
>>>>>>> c623c2ec8d60c2a9916e1820505f8cec653d2158
}

void Model::deleteSlot(Slot* slot) {
    cout << "erasing slot : " << slot->toString() << endl;
    this->slotlist.erase(slot);
    //TODO : delete les *slots
}

void Model::cleanList() {
    for(ListOfSlot::iterator it = this->slotlist.begin();  it != this->slotlist.end(); it++) {
        delete *it;
    }
    this->slotlist.clear();
}


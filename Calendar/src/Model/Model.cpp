/* 
 * File:   Model.cpp
 * Author: e094326d
 * 
 * Created on 18 novembre 2012, 11:44
 */

#include <qt4/QtCore/qglobal.h>

#include "../../headers/Model/Model.hpp"
#include "View.hpp"


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
    for (unsigned int i = 0 ; i < 7 ; i++) {
        this->currentDate->nextDay();
	}
}
void Model::previousWeek() {
    for (unsigned int i = 0 ; i < 7 ; i++) {
        this->currentDate->previousDay();
	}
}

Slot* Model::createSlot(Time *dateDeb, Time *dateFin, string intitule, string description, string location) {
    Slot *newSlot = new Slot(dateDeb, dateFin, intitule, description, location);

    cout << "inserting slot : " << newSlot->toString() << endl;
    
    this->slotlist.insert(newSlot);
    
    return newSlot;

}

void Model::deleteSlot(ListOfSlot::iterator it) {
    cout << "erasing slot from iterator : " << (*it)->toString() << endl;
    this->slotlist.erase(it);
}

void Model::deleteSlot(Slot* slot) {
    cout << "erasing slot : " << slot->toString() << endl;
    this->slotlist.erase(slot);
    delete slot;
}

void Model::cleanList() {
    for(ListOfSlot::iterator it = this->slotlist.begin();  it != this->slotlist.end(); it++) {
        delete *it;
    }
    this->slotlist.clear();
}


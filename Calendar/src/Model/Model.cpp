/* 
 * File:   Model.cpp
 * Author: e094326d
 * 
 * Created on 18 novembre 2012, 11:44
 */

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

void Model::createSlot(Time *dateDeb, Time *dateFin, string intitule, string description) {
    Slot *newSlot = new Slot(dateDeb, dateFin, intitule, description);
    this->slotlist.insert(newSlot);
    
    if(dateDeb > dateFin)

    cout << "inserting slot : " << newSlot->toString() << endl;
    

    // Si le slot existe déjà
    if(this->exists(newSlot))
        delete newSlot;
    else
        this->slotlist.insert(newSlot);

}

void Model::deleteSlot(ListOfSlot::iterator it) {
    cout << "erasing slot : " << (*it)->toString() << endl;
    this->slotlist.erase(it);
}

void Model::deleteSlot(Slot* slot) {
    this->slotlist.erase(slot);
}

bool Model::exists(Slot* slot) {
    return false;
}
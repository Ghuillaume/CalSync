/* 
 * File:   Model.cpp
 * Author: e094326d
 * 
 * Created on 18 novembre 2012, 11:44
 */

#include "../../headers/Model/Model.hpp"


bool compareDate(Slot first, Slot second) {
	return (first.getDateDebut() < second.getDateFin());
}

Model::Model() {

}

Model::~Model() {
}

ListOfSlot Model::getSlotList() {
    return this->slotlist;
}

void Model::createSlot(Time *dateDeb, Time *dateFin, string intitule) {
	Slot *newSlot = new Slot(dateDeb, dateFin, intitule);
	this->slotlist.push_back(newSlot);
        
        // TODO
	// On regarde si le slot existe déjà
        /*
	if(this->exists(newSlot))
		delete newSlot;
	else {
		this->slotlist.push_back(newSlot);
		this->slotlist.sort(compareDate);
	}*/

}

bool Model::exists(Slot* slot) {
    
    // TODO
    return false;
}
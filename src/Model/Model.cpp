/* 
 * File:   Model.cpp
 * Author: e094326d
 * 
 * Created on 18 novembre 2012, 11:44
 */

#include "Model.hpp"

Model::Model() {

}

Model::~Model() {
}

void Model::createSlot(Time &dateDeb, Time &dateFin, string intitule) {
	Slot *newSlot = new Slot(dateDeb, dateFin, intitule);
	
	// On regarde si le slot existe déjà
	if(this->exists(newSlot))
		delete newSlot;
	else {
		this->slots->push_back(newSlot);
		this->slots->sort(Slot.compareDate);
	}

}

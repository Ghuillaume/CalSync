/* 
 * File:   Slot.cpp
 * Author: e094326d
 * 
 * Created on 18 novembre 2012, 11:44
 */

#include "../../headers/Model/Slot.hpp"

Slot::Slot(Time *dateDebut, Time *dateFin, string intitule, string description) {
    this->dateDebut = dateDebut;
    this->dateFin = dateFin;
    this->intitule = intitule;
    this->description = description;
}

Slot::~Slot() {
}

bool  Slot::operator== ( const Slot &slot ) const {
	return(	this->dateDebut == slot.dateDebut &&
			this->dateFin == slot.dateFin &&
            this->intitule == slot.intitule &&
            this->description == slot.description);
}
bool  Slot::operator!= ( const Slot &slot ) const {
	return(	this->dateDebut != slot.dateDebut ||
			this->dateFin != slot.dateFin ||
            this->intitule != slot.intitule ||
            this->description != slot.description);
}


        
Time* Slot::getDateDebut() {
	return this->dateDebut;
}

Time* Slot::getDateFin() {
	return this->dateFin;
}

string Slot::getIntitule() {
    return this->intitule;
}

string Slot::getDescription() {
    return this->description;
}

void Slot::setDateDebut(Time *t) {
	this->dateDebut = t;
}
void Slot::setDateFin(Time *t) {
	this->dateFin = t;
}

void Slot::setIntitule(string intitule) {
    this->intitule = intitule;
}

void Slot::setDescription(string description) {
    this->description = description;
}

bool Slot::areSlotsOverlapping(Slot *newSlot) {
    /*
    return ( ( ((*this->dateDebut) <= (*newSlot->dateDebut)) && ((*newSlot->dateDebut) < (*this->dateFin)) )
             || ( ((*this->dateDebut) < (*newSlot->dateFin)) && ((*newSlot->dateFin) <= (*this->dateFin)) )
            );
    */
    // slot commence avant ou égal a dateFin ET slot fini après ou égal à dateDebut
    return ( (*(newSlot->dateDebut) < *(this->dateFin)) && (*(newSlot->dateFin) > *(this->dateDebut)));
}


int Slot::editSlot(Time *dateDebut, Time *dateFin, string intitule, string description) {
    this->dateDebut = dateDebut;
    this->dateFin = dateFin;
    this->intitule = intitule;
    this->description = description;

    int code = 0;
    // TODO : vérifier cohérence date début et date fin

    return code;
}

string Slot::toString() {
    
    return this->dateDebut->getDate() + " " + this->intitule
            + " (end " + this->dateFin->getDate() + ")";
}

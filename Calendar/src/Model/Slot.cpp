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
    
    // TODO : vérifier cohérence date début et date fin
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

void Slot::editSlot(Time *dateDebut, Time *dateFin, string intitule, string description) {
    this->dateDebut = dateDebut;
    this->dateFin = dateFin;
    this->intitule = intitule;
    this->description = description;

    // TODO : vérifier cohérence date début et date fin
}

string Slot::toString() {
    ostringstream hdeb, hfin;
    hdeb << this->dateDebut->getHour() << "h" << this->dateDebut->getMinute();
    hfin << this->dateFin->getHour() << "h" << this->dateFin->getMinute();
    
    return this->dateDebut->getDate() + " " + hdeb.str() + " : " + this->intitule
            + " (end " + this->dateFin->getDate() + " " + hfin.str() + ")";
}

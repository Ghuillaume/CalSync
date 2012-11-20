/* 
 * File:   Slot.cpp
 * Author: e094326d
 * 
 * Created on 18 novembre 2012, 11:44
 */

#include "../../headers/Model/Slot.hpp"

Slot::Slot(Time *dateDebut, Time *dateFin, string intitule) {
    this->dateDebut = dateDebut;
    this->dateFin = dateFin;
    this->intitule = intitule;
    
    // TODO : vérifier cohérence date début et date fin
}

Slot::~Slot() {
}

bool  Slot::operator== ( const Slot &slot ) const {
	return(	this->dateDebut == slot.dateDebut &&
			this->dateFin == slot.dateFin &&
			this->intitule == slot.intitule);
}
bool  Slot::operator!= ( const Slot &slot ) const {
	return(	this->dateDebut != slot.dateDebut ||
			this->dateFin != slot.dateFin ||
			this->intitule != slot.intitule);
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

void Slot::setDateDebut(Time *t) {
	this->dateDebut = t;
}
void Slot::setDateFin(Time *t) {
	this->dateFin = t;
}

void Slot::setIntitule(string intitule) {
	this->intitule = intitule;
}

string Slot::toString() {
    ostringstream hdeb, hfin;
    hdeb << this->dateDebut->getHour() << "h" << this->dateDebut->getMinute();
    hfin << this->dateFin->getHour() << "h" << this->dateFin->getMinute();
    
    return this->dateDebut->getDate() + " " + hdeb.str() + " to " +
            this->dateFin->getDate() + " " + hfin.str() + " -> " + this->intitule;
}
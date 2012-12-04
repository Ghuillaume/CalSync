/* 
 * File:   Slot.cpp
 * Author: e094326d
 * 
 * Created on 18 novembre 2012, 11:44
 */

#include "../../headers/Model/Slot.hpp"

Slot::Slot(Time *dateDebut, Time *dateFin, string intitule, string description, string location) {
    this->dateDebut = dateDebut;
    this->dateFin = dateFin;
    this->intitule = intitule;
    this->description = description;
    this->location = location;
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

string Slot::getLocation() {
    return this->location;
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


void Slot::setLocation(string location) {
    this->location = location;
}

bool Slot::areSlotsOverlapping(Time* dateDebut, Time* dateFin) {
    // The slot begins before or at dateFin and it ands after or at dateDebut
    return ( (*(dateDebut) < *(this->dateFin)) && (*(dateFin) > *(this->dateDebut)));
}


void Slot::editSlot(Time *dateDebut, Time *dateFin, string intitule, string description) {
    this->dateDebut = dateDebut;
    this->dateFin = dateFin;
    this->intitule = intitule;
    this->description = description;
}

string Slot::toString() {
    
    return this->dateDebut->getReadableDate() + " " + this->intitule
            + " (end " + this->dateFin->getReadableDate() + ")";
}

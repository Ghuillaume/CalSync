/* 
 * File:   Slot.h
 * Author: e094326d
 *
 * Created on 18 novembre 2012, 11:44
 */

#ifndef SLOT_H
#define	SLOT_H

#include "Time.hpp"
#include "common.h"

class Slot {

	public:
        Slot(Time *dateDebut, Time *dateFin, string intitule,
				string description, string location);
        virtual ~Slot();

        bool  operator== ( const Slot &slot ) const;
        bool  operator!= ( const Slot &slot ) const;

        Time* getDateDebut();
        Time* getDateFin();
        string getIntitule();
        string getDescription();
        string getLocation();
        bool areSlotsOverlapping(Time* dateDebut, Time* dateFin);
        void setDateDebut(Time *t);
        void setDateFin(Time *t);
        void setIntitule(string intitule);
        void setDescription(string description);
        void setLocation(string location);
        void editSlot(Time *dateDebut, Time *dateFin, string intitule,
						string description, string location);

        string toString();
		
		
	private:
		Time *dateDebut;
		Time *dateFin;
		string intitule;
        string description;
        string location;
		
	
};

#endif

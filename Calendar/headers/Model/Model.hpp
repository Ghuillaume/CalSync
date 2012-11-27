/* 
 * File:   Model.h
 * Author: e094326d
 *
 * Created on 18 novembre 2012, 11:44
 */

#ifndef MODEL_H
#define	MODEL_H

using namespace std;

#include "common.h"
#include "Slot.hpp"
#include "Time.hpp"

struct classcomp {
  bool operator() (Slot* first, Slot* second) const
  {return ( *(first->getDateDebut()) < *(second->getDateDebut()) );}
};


typedef set<Slot*, classcomp> ListOfSlot;

class Model {
	public:
            Model();
            virtual ~Model();

            ListOfSlot getSlotList();
            Time* getCurrentDate();
            void nextWeek();
            void previousWeek();

            int createSlot(Time *dateDeb, Time *dateFin, string intitule, string description);
            void deleteSlot(ListOfSlot::iterator it);
            void deleteSlot(Slot *slot);
            bool exists(Slot *slot);

	private:
            Time* currentDate;
            ListOfSlot slotlist;
};

#endif	/* MODEL_H */

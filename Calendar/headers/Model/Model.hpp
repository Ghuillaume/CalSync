#ifndef MODEL_H
#define	MODEL_H

#include <QtCore>

using namespace std;

#include "common.h"
#include "Slot.hpp"
#include "Time.hpp"
#include "View.hpp"

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

            Slot* createSlot(Time *dateDeb, Time *dateFin, string intitule, string description, string location);
            void deleteSlot(ListOfSlot::iterator it);
            void deleteSlot(Slot *slot);
            void cleanList();

	private:
            Time* currentDate;
            ListOfSlot slotlist;
};

#endif  

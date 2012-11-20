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


class Model {
	public:
      		Model();
		virtual ~Model();
                
                ListOfSlot getSlotList();
	
		void createSlot(Time *dateDeb, Time *dateFin, string intitule);
		bool exists(Slot *slot);
		
	private:
		ListOfSlot slotlist;
};

#endif	/* MODEL_H */
/* 
 * File:   Model.h
 * Author: e094326d
 *
 * Created on 18 novembre 2012, 11:44
 */

#ifndef MODEL_H
#define	MODEL_H

#include "common.h"
#include "Slot.hpp"
#include "Time.hpp"

#include <list>
typedef list<Slot*> ListOfSlot;

class Model {
	public:
		Model();
		virtual ~Model();
	
		void createSlot(Time &dateDeb, Time &dateFin, string intitule);
		bool exists(Slot *slot);
		bool isSlotFree(Slot &slot);
		
		bool saveModel();
		bool loadModel();
		
	private:
		list<Slot*> slots;
};

#endif	/* MODEL_H */
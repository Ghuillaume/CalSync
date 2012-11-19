#ifndef _CONTROLLER_HPP_
#define _CONTROLLER_HPP_

#include <QtGui>

#include "../Model/Model.hpp"
#include "../View/View.hpp"
#include "DateDialog.hpp"
#include "ModuleDialog.hpp"
#include "GroupDialog.hpp"
#include "TeacherDialog.hpp"
#include "RoomDialog.hpp"
#include "SlotDialog.hpp"

class Controller : public QWidget {
    Q_OBJECT
    public:
        Controller(Model *modele, View *view);
        ~Controller();

    public slots:
        void selectWeek();
	    void createSlot(int row, int column);

    private:
        Model *model;
        View *view;
};


#endif

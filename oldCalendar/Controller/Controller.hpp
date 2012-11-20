#ifndef _CONTROLLER_HPP_
#define _CONTROLLER_HPP_

#include <QtGui>

#include "../Model/Model.hpp"
#include "../View/View.hpp"
#include "../View/DateDialog.hpp"
#include "../View/SlotDialog.hpp"

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

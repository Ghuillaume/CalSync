#ifndef _CONTROLER_HPP_
#define _CONTROLER_HPP_

#include <QtGui>

#include "Config.hpp"
#include "../Model/Model.hpp"
#include "../View/View.hpp"
#include "../View/DateDialog.hpp"
#include "../View/SlotDialog.hpp"

class Controler : public QWidget {
    Q_OBJECT
    public:
        Controler(Model* modele, View* view, Config* config);
        ~Controler();

    public slots:
        void selectWeek();
        void createSlot();
        void editSlot();
        void deleteSlot();
        void saveModel();
        void loadModel();
        void checkIfSaved();
        void changePassword();
        void changeAPIKey();

    private:
        Model* model;
        View* view;
        Config* config;
};


#endif

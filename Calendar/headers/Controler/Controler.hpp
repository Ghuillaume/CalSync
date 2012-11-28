#ifndef _CONTROLER_HPP_
#define _CONTROLER_HPP_

#include <QtGui>

#include "Config.hpp"
#include "md5.hpp"
#include "../Model/Model.hpp"
#include "../View/View.hpp"
#include "../View/DateDialog.hpp"
#include "../View/SlotDialog.hpp"
#include "../Parser/ParserGCal.hpp"
#include "../Parser/ParserCELCAT.hpp"

class Controler : public QWidget {
    Q_OBJECT
    public:
        Controler(Model* modele, View* view, Config* config);
        ~Controler();
        void setMainFrameConnections();

    public slots:
        void newEmptyModel();
        void newModelFromLocal();
        void newModelFromGoogle();
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

#ifndef _CONTROLER_HPP_
#define _CONTROLER_HPP_

#include <QtGui>

#include "Config.hpp"
#include "md5.hpp"
#include "OAuth.hpp"
#include "../Model/Model.hpp"
#include "../View/View.hpp"
#include "../View/DateDialog.hpp"
#include "../View/SlotDialog.hpp"
#include "../View/GoogleAccessDialog.hpp"
#include "../Parser/ParserGCal.hpp"
#include "../Parser/ParserCELCAT.hpp"

typedef std::vector<std::string> ListOfString;

class Controler : public QWidget {
    Q_OBJECT
    public:
        Controler(Model* modele, View* view, Config* config);
        ~Controler();
        int checkIfSaved();
        void parseModel(QString fileName);
        static ListOfString explode(const std::string& str, const char& delimiter);

    public slots:
        void setStartView();
        void newEmptyModel();
        void newModelFromLocal();
        void newModelFromGoogle();
        //void selectWeek();
        void createSlot();
        void editSlot();
        void deleteSlot();
        void saveModel();
        void saveModelAs();
        void loadModel();
        void close();
        void changePassword();
        void changeAPIKey();
        void getGoogleAccessToken();
        void googleAccessTokenObtained(QString authCode);

    private:
        Model* model;
        View* view;
        Config* config;
        OAuth2* auth2;
};


#endif

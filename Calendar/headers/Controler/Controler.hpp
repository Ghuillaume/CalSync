#ifndef _CONTROLER_HPP_
#define _CONTROLER_HPP_

#include <QtGui>
#include <QtXml>
#include <QDomDocument>

#include "Config.hpp"
#include "md5.hpp"
#include "OAuth.hpp"
#include "../Model/Model.hpp"
#include "../Model/common.h"
#include "../View/View.hpp"
#include "../View/DateDialog.hpp"
#include "../View/SlotDialog.hpp"
#include "../View/SettingsDialog.hpp"
#include "../View/GoogleAccessDialog.hpp"
#include "../Parser/ParserGCal.hpp"
#include "../Parser/ParserCELCAT.hpp"

class Controler : public QWidget {
    Q_OBJECT
    public:
        Controler(Model* modele, View* view, Config* config);
        ~Controler();
        int checkIfSaved();
        void parseModel(QString fileName);
        static Time* createTime(const QString &chaine);

        void connectAllButtons();

    public slots:
        void setStartView();
        void newEmptyModel();
        void newModelFromLocal();
        void newModelFromGoogle();
        void clickSlot();
        void createSlot();
        void editSlot();
        void deleteSlot();
        void saveModel();
        void saveModelAs();
        void loadModel();
        void close();
        void updateSettings();
        void changePassword();
        void changeAPIKey();
        void getGoogleAccessToken();
        void googleCodeObtained(QString authCode);
        void googleAccessTokenObtained(QString token);
        void importCalendar();
        void exportCalendar();
        
        void previousWeek();
        void nextWeek();

    private:
        Model* model;
        View* view;
        Config* config;
        OAuth2* auth2;
};


#endif

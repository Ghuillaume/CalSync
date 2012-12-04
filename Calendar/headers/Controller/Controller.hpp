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
#include "SlotFrame.hpp"

class Controller : public QWidget {
    Q_OBJECT
    public:
        Controller(Model* modele, View* view, Config* config);
        ~Controller();

        void checkConflicts(Time* start, Time* end, Slot* currentSlot);
        int checkIfSaved();
        bool checkGoogleAuth();
        void parseModel(QString fileName);
        static Time* createTime(const QString &chaine);
        void connectAllSlots();

    public slots:
        void setStartView();
        void newEmptyModel();
        void newModelFromLocal();
        void newModelFromGoogle();
        void askCalendarList();
        void selectCalendar(QNetworkReply* list);
        void clickSlot(SlotFrame *frame);
        void createSlot();
        void editSlot(SlotFrame *frame);
        void deleteSlot();
        void saveModel();
        void saveModelAs();
        void loadModel();
        void close();
        void updateSettings();
        void updateGCalID(int i);
        void updateOnlineService(QString service);
        void updateAcademicSchedule(QString schedule);
        void changePassword();
        void getGoogleAccessToken();
        void googleCodeObtained(QString authCode);
        void googleAccessTokenObtained(QString token);
        void importCalendar();
        void exportCalendar();
        
        void previousWeek();
        void nextWeek();

    signals:
        void tokenSaved();

    private:
        Model* model;
        View* view;
        Config* config;
        OAuth2* auth2;
};


#endif

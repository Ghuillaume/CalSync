#ifndef CONFIG_HPP
#define CONFIG_HPP

#include "../Model/common.h"
#include "OAuth.hpp"

class Config {
    public:
        Config();
        ~Config();

        void setSaved(bool saved);
        string getPassword();
        void setPassword(string pwd);
        string getOnlineService();
        void setOnlineService(string service);
        string getAcademicSchedule();
        void setAcademicSchedule(string schedule);
        QString getGCalId();
        void setGCalId(QString id);
        QString getFileName();
        void setFileName(QString& filename);
        QString getGoogleAuthCode();
        void setGoogleAuthCode(QString authcode);
        OAuth2* getGoogleOAuth();
        void setGoogleOAuth(OAuth2* oauth);
        QVariantList* getCalendarList();
        void setCalendarList(QVariantList* list);
        QString getCelcatGroup();
        void setCelcatGroup(QString group);

        bool isSaved();
        void clean();


    private:
        bool saved;
        string password;
        string onlineService;
        string academicSchedule;
        QString gCalId;
        QString googleAuthCode;
        OAuth2* oauth2;
        QString celcatGroup;
        
        QString savefileName;

        QVariantList* calendarList;

};

#endif // CONFIG_HPP

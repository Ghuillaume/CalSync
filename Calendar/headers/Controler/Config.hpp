#ifndef CONFIG_HPP
#define CONFIG_HPP

#include "../Model/common.h"
#include "OAuth.hpp"

class Config {
    public:
        Config();
        ~Config();

        bool isSaved();
        void setSaved(bool saved);
        string getPassword();
        void setPassword(string pwd);
        string getGCalId();
        void setGCalId(string id);
        string getAPIKEY();
        void setAPIKEY(string key);
        QString getFileName();
        void setFileName(QString& filename);
        void clean();

        QString getGoogleAuthCode();
        void setGoogleAuthCode(QString& authcode);
        OAuth2* getGoogleOAuth();
        void setGoogleOAuth(OAuth2* oauth);

    private:
        bool saved;
        string password;
        string gCalId;
        string API_KEY;
        QString googleAuthCode;
        OAuth2* oauth2;
        
        QString savefileName;

};

#endif // CONFIG_HPP

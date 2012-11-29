#ifndef CONFIG_HPP
#define CONFIG_HPP

#include "../Model/common.h"

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

    private:
        bool saved;
        string password;
        string gCalId;
        string API_KEY;
        
        QString savefileName;

};

#endif // CONFIG_HPP

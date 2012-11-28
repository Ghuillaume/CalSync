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
        string getAPIKEY();
        void setAPIKEY(string key);

    private:
        bool saved;
        string password;
        string API_KEY;

};

#endif // CONFIG_HPP
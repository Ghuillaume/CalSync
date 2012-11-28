#include "../../headers/Controler/Config.hpp"

Config::Config()
{
    this->password = "0";
    this->saved = true;
    this->API_KEY = "0";
}

Config::~Config() {

}

bool Config::isSaved() {
    return this->saved;
}

void Config::setSaved(bool saved) {
    this->saved = saved;
}

string Config::getPassword() {
    return this->password;
}

void Config::setPassword(string pwd) {
    this->password = pwd;
}

string Config::getAPIKEY() {
    return this->API_KEY;
}

void Config::setAPIKEY(string key) {
    this->API_KEY = key;
}

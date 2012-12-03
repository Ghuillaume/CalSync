#include "../../headers/Controller/Config.hpp"

Config::Config()
{
    this->password = "";
    this->saved = true;
    this->API_KEY = "";
    this->googleAuthCode = "";
    this->savefileName = "";
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

string Config::getGCalId() {
    return this->gCalId;
}

void Config::setGCalId(string key) {
    this->gCalId = key;
}


string Config::getAPIKEY() {
    return this->API_KEY;
}

void Config::setAPIKEY(string key) {
    this->API_KEY = key;
}

QString Config::getFileName() {
    return this->savefileName;
}

void Config::setFileName(QString& filename) {
    this->savefileName = filename;
}

void Config::clean() {
    this->password = "";
    this->saved = true;
    this->API_KEY = "";
    this->googleAuthCode = "";
    this->savefileName = "";
}

QString Config::getGoogleAuthCode() {
    return this->googleAuthCode;
}

void Config::setGoogleAuthCode(QString authcode) {
    this->googleAuthCode = authcode;
}

OAuth2* Config::getGoogleOAuth() {
    return this->oauth2;
}

void Config::setGoogleOAuth(OAuth2* oauth) {
    this->oauth2 = oauth;
}

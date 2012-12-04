#include "../../headers/Controller/Config.hpp"

Config::Config()
{
    this->password = "";
    this->saved = true;
    this->onlineService = "Google Calendar";
    this->academicSchedule = "UnivNantes (CELCAT)";
    this->googleAuthCode = "";
    this->savefileName = "";
    this->calendarList = new QVariantList;
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

string Config::getOnlineService() {
    return this->onlineService;
}

void Config::setOnlineService(string service)  {
    this->onlineService = service;
}

string Config::getAcademicSchedule() {
    return this->academicSchedule;
}

void Config::setAcademicSchedule(string schedule) {
    this->academicSchedule = schedule;
}

QString Config::getGCalId() {
    return this->gCalId;
}

void Config::setGCalId(QString id) {
    this->gCalId = id;
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

QVariantList* Config::getCalendarList() {
    return this->calendarList;
}

void Config::setCalendarList(QVariantList* list) {
    this->calendarList = list;
}

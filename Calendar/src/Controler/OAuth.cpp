#include "../../headers/Controler/OAuth.hpp"
#include <QDebug>
#include <QApplication>
#include "../View/GoogleAccessDialog.hpp"
#include <QSettings>
#include <QMessageBox>

OAuth2::OAuth2(QWidget* parent)
{
    m_strEndPoint = "https://accounts.google.com/o/oauth2/auth";
    m_strScope = "https://www.googleapis.com/auth/calendar"; //Access to Calendar service
    m_strClientID = "472547521565-bh8dk3m0kacs9lrjndglns497af1j3k7.apps.googleusercontent.com";
    m_strRedirectURI = "urn:ietf:wg:oauth:2.0:oob";
    m_strClientSecret = "w6JKanm6XHjTZttgUo82Bd9w";
    m_strResponseType = "code";

    m_pGoogleAccessDialog = new GoogleAccessDialog(parent);
    m_pParent = parent;
    connect(m_pGoogleAccessDialog, SIGNAL(codeObtained(QString)),this,SLOT(codeObtained(QString)));
}



void OAuth2::accessTokenObtained(QString access_token)
{
    QSettings settings("ICS", "Google API Calendar Client");
    m_strAccessToken = access_token;
    settings.setValue("access_token", m_strAccessToken);
    m_pGoogleAccessDialog->setLoginUrl("");
    emit loginDone();

}

void OAuth2::codeObtained(QString code) {

    emit sigCodeObtained(code);
}


QString OAuth2::loginUrl()
{
    QString str = QString("%1?client_id=%2&redirect_uri=%3&response_type=%4&scope=%5").arg(m_strEndPoint).arg(m_strClientID).
            arg(m_strRedirectURI).arg(m_strResponseType).arg(m_strScope);
    qDebug() << "Login URL" << str;
    return str;
}

QString OAuth2::getCode() const{
    return m_strCode;
}

QString OAuth2::getClientID() const {
    return m_strClientID;
}

QString OAuth2::getClientSecret() const {
    return m_strClientSecret;
}

QString OAuth2::getRedirectURI() const{
    return m_strRedirectURI;
}

QString OAuth2::accessToken()
{
    return m_strAccessToken;
}

bool OAuth2::isAuthorized()
{
    return m_strAccessToken != "";
}

void OAuth2::startLogin(bool bForce)
{
    qDebug() << "OAuth2::startLogin";
    QSettings settings("ICS", "Google API Calendar Client");
    QString str = settings.value("access_token", "").toString();

    qDebug() << "OAuth2::startLogin, token from Settings" << str;

    if(str.isEmpty() || bForce)
    {
        m_pGoogleAccessDialog->setLoginUrl(loginUrl());
        m_pGoogleAccessDialog->show();
    }
    else
    {
        m_strAccessToken = str;
        emit loginDone();
    }
}



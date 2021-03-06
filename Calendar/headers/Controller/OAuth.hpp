#ifndef OAUTH_HPP
#define OAUTH_HPP

#include <iostream>
#include <QString>
#include <QObject>
#include <QDebug>
#include <QApplication>

#include <QByteArray>
#include <QNetworkReply>
#include <QNetworkAccessManager>
#include <QSettings>
#include <QMessageBox>

#include <QJson/Parser>
#include "../View/GoogleAccessDialog.hpp"

class GoogleAccessDialog;

class OAuth2 : public QObject
{
    Q_OBJECT

public:
    OAuth2(QWidget* parent = 0);
    QString accessToken();
    bool isAuthorized();
    void startLogin(bool bForce);
    void askTokenAccess(QString code);
    void accessTokenObtained(QString access_token);

    QString loginUrl();

    QString getCode() const;
    QString getClientID() const;
    QString getClientSecret() const;
    QString getRedirectURI() const;

signals:
    void loginDone();
    void sigCodeObtained(QString);
    void tokenObtained(QString);

private slots:

    void codeObtained(QString code);
    void replyFinished(QNetworkReply * reply);

private:
    QString m_strAccessToken;
    QString m_strCode;

    QString m_strEndPoint;
    QString m_strScope;
    QString m_strClientID;
    QString m_strClientSecret;
    QString m_strRedirectURI;
    QString m_strResponseType;

    GoogleAccessDialog* m_pGoogleAccessDialog;
    QWidget* m_pParent;

    QNetworkAccessManager* networkManager;
};


#endif // OAUTH_HPP

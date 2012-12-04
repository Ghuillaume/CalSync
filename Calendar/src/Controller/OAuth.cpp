#include "../../headers/Controller/OAuth.hpp"

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

    networkManager = new QNetworkAccessManager(this);
    connect(networkManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished(QNetworkReply*)));

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


void OAuth2::askTokenAccess(QString code) {

    QString url = QString("https://accounts.google.com/o/oauth2/token");
    QString params = QString("code=%1&client_id=%2&client_secret=%3&redirect_uri=%4&grant_type=authorization_code")
            .arg(code)
            .arg(this->m_strClientID)
            .arg(this->m_strClientSecret)
            .arg(this->m_strRedirectURI);
    QNetworkRequest request;
    request.setUrl(url);
    request.setRawHeader("Content-Type", "application/x-www-form-urlencoded");
    QApplication::setOverrideCursor(Qt::WaitCursor);
    this->networkManager->post(request, QByteArray(params.toUtf8()));
}


void OAuth2::replyFinished(QNetworkReply * reply)
{

    QApplication::restoreOverrideCursor();
    QString token = "";
    QString json = reply->readAll();

    QApplication::restoreOverrideCursor();

    QJson::Parser parser;
    bool ok;
    QVariant result = parser.parse(json.toLatin1(), &ok);
    if(!ok) {
        qCritical() << "error json -> authcode";
    }
    if(result.toMap().contains("access_token")) {
        token = result.toMap()["access_token"].toString();
    }

    emit tokenObtained(token);
}

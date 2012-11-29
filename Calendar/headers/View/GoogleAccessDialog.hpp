#ifndef GOOGLEACCESSDIALOG_HPP
#define GOOGLEACCESSDIALOG_HPP

#include <iostream>
#include <QDialog>
#include <QString>
#include <QUrl>
#include <QWebView>
#include <QWebFrame>
#include <QtGui>

class GoogleAccessDialog : public QDialog
{
    Q_OBJECT

public:
    explicit GoogleAccessDialog(QWidget *parent = 0);
    ~GoogleAccessDialog();
    void setLoginUrl(const QString& url);
    QString accessToken();
    QString code();

signals:
    void accessTokenObtained();
    void codeObtained(QString);

private slots:
    void urlChanged(const QUrl& url);
    void loadStarted();
    void loadFinished(bool);


private:

    QWebView* webView;
    QString m_strAccessToken;
    QString m_strCode;
};

#endif // GOOGLEACCESSDIALOG_HPP

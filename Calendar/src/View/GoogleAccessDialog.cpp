#include "../../headers/View/GoogleAccessDialog.hpp"
#include <QDebug>


GoogleAccessDialog::GoogleAccessDialog(QWidget *parent) : QDialog(parent) {

    this->setWindowTitle("Connexion au service Google");
    this->resize(548,456);
    QGridLayout *gridLayout = new QGridLayout(this);
    webView = new QWebView(this);
    QDialogButtonBox *buttonBox = new QDialogButtonBox(this);

    webView->setUrl(QUrl(QString::fromUtf8("about:blank")));

    buttonBox->setOrientation(Qt::Horizontal);
    buttonBox->setStandardButtons(QDialogButtonBox::Close);

    gridLayout->addWidget(webView, 0, 0, 1, 1);
    gridLayout->addWidget(buttonBox, 1, 0, 1, 1);

    QObject::connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    QObject::connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
    QObject::connect(webView,SIGNAL(urlChanged(QUrl)),this,SLOT(urlChanged(QUrl)));
    QObject::connect(webView,SIGNAL(loadStarted()),this,SLOT(loadStarted()));
    QObject::connect(webView,SIGNAL(loadFinished(bool)),this,SLOT(loadFinished(bool)));

}

GoogleAccessDialog::~GoogleAccessDialog() {

}

void GoogleAccessDialog::loadStarted()
{
    QApplication::setOverrideCursor(Qt::WaitCursor);
    qDebug() << "loadStarted";
}

void GoogleAccessDialog::loadFinished(bool b)
{

    QString str = webView->title();
    qDebug() << "title =" << str;
    if(str.indexOf("code") != -1)
    {
        std::cout <<"on rentre la :" << str.toStdString() <<std::endl;
        QStringList pair = str.split("=");
        if (pair[0] == "Success code")
        {
            m_strCode = pair[1];
            emit codeObtained(m_strCode);
            QDialog::accept();
        }
    }
    QApplication::restoreOverrideCursor();
    qDebug() << "loadFinished with" << b;
}

void GoogleAccessDialog::urlChanged(const QUrl &url)
{

}

QString GoogleAccessDialog::accessToken()
{
    return m_strAccessToken;
}

QString GoogleAccessDialog::code() {
    return m_strCode;
}


void GoogleAccessDialog::setLoginUrl(const QString& url)
{
   webView->setUrl(QUrl(url));
}



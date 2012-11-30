#include "../../headers/View/SettingsDialog.hpp"

SettingsDialog::SettingsDialog(QWidget* parent):
    QDialog ( parent )
{
    this->parent = (View*) parent;

    this->setObjectName("Dialog");
    this->resize(500,600);
    this->setWindowTitle(QString::fromUtf8("Edit settings"));

    frame = new QWidget(this);
    frame->setObjectName("frame");
    frame->setGeometry(QRect(10, 10, this->width(), this->height()));

    formLayoutWidget = new QWidget(frame);
    formLayoutWidget->setObjectName(QString::fromUtf8("formLayoutWidget"));
    formLayout = new QFormLayout(formLayoutWidget);
    formLayout->setObjectName(QString::fromUtf8("formLayout"));
    formLayout->setContentsMargins(0, 0, 0, 0);


    // Display labels

    serviceLabel = new QLabel(formLayoutWidget);
    serviceLabel->setObjectName("serviceLabel");
    serviceLabel->setText("Service");
    formLayout->setWidget(1, QFormLayout::LabelRole, serviceLabel);

    idCalendarLabel = new QLabel(formLayoutWidget);
    idCalendarLabel->setObjectName("idCalendarLabel");
    idCalendarLabel->setText("Google Calendar ID");
    formLayout->setWidget(2, QFormLayout::LabelRole, idCalendarLabel);

    googleAuthLabel = new QLabel(formLayoutWidget);
    googleAuthLabel->setObjectName("googleAuthLabel");
    googleAuthLabel->setText("Google Authentication required"); // change to OK when user is authenticated
    formLayout->setWidget(3, QFormLayout::LabelRole, googleAuthLabel);

    QSpacerItem *horizontalSpacer1 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
    formLayout->setItem(4, QFormLayout::SpanningRole, horizontalSpacer1);

    inputCalendarLabel = new QLabel(formLayoutWidget);
    inputCalendarLabel->setObjectName("inputCalendarLabel");
    inputCalendarLabel->setText("Import calendar from");
    formLayout->setWidget(5, QFormLayout::LabelRole, inputCalendarLabel);




    // Display parameters edition

    pwdButton = new QPushButton(formLayoutWidget);
    pwdButton->setObjectName(QString::fromUtf8("pwdButton"));
    pwdButton->setText("Change my password");
    formLayout->setWidget(0, QFormLayout::SpanningRole, pwdButton);

    // pos1 : selection box

    idCalendarEdit = new QLineEdit(formLayoutWidget);
    idCalendarEdit->setObjectName(QString::fromUtf8("idCalendarEdit"));
    formLayout->setWidget(2, QFormLayout::FieldRole, idCalendarEdit);

    googleAuthButton = new QPushButton(formLayoutWidget);
    googleAuthButton->setObjectName(QString::fromUtf8("googleAuthButton"));
    googleAuthButton->setText("OAuth2.0");
    formLayout->setWidget(3, QFormLayout::FieldRole, googleAuthButton);

    // pos5 = selection box



    QSpacerItem *horizontalSpacer2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
    formLayout->setItem(6, QFormLayout::SpanningRole, horizontalSpacer2);

    buttonBox = new QDialogButtonBox(formLayoutWidget);
    buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
    buttonBox->setOrientation(Qt::Horizontal);
    buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
    formLayout->setWidget(7, QFormLayout::SpanningRole, buttonBox);
}


SettingsDialog::~SettingsDialog()
{
    delete parent;
    delete frame;
}



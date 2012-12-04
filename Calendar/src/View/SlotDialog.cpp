#include "../../headers/View/SlotDialog.hpp"

SlotDialog::SlotDialog(QWidget* parent):
    QDialog ( parent ),
    time    ()
{
    this->parent = (View*) parent;


    Time parentTime = *(this->parent->getTime());
    time.setDate (
        parentTime.getMinute  (),
        parentTime.getHour  (),
        parentTime.getDay   (),
        parentTime.getMonth (),
        parentTime.getYear  ()
    );

    this->setObjectName("Dialog");
    this->resize(300, 230);
    this->setWindowTitle(QString::fromUtf8("Create a new event"));

    frame = new QWidget(this);
    frame->setObjectName("frame");
    frame->setGeometry(QRect(10, 10, 300, 230));

    formLayoutWidget = new QWidget(frame);
    formLayoutWidget->setObjectName(QString::fromUtf8("formLayoutWidget"));
    //formLayoutWidget->setGeometry(QRect(350, 100, 311, 251));
    formLayout = new QFormLayout(formLayoutWidget);
    formLayout->setObjectName(QString::fromUtf8("formLayout"));
    formLayout->setContentsMargins(0, 0, 0, 0);


    // Display labels
    dateStartLabel = new QLabel(formLayoutWidget);
    dateStartLabel->setObjectName("dateStartLabel");
    dateStartLabel->setText("Start date :");
    formLayout->setWidget(0, QFormLayout::LabelRole, dateStartLabel);

    dateEndLabel = new QLabel(formLayoutWidget);
    dateEndLabel->setObjectName("dateEndLabel");
    dateEndLabel->setText("End date :");
    formLayout->setWidget(1, QFormLayout::LabelRole, dateEndLabel);

    titleLabel = new QLabel(formLayoutWidget);
    titleLabel->setObjectName("titleLabel");
    titleLabel->setText("Title :");
    formLayout->setWidget(2, QFormLayout::LabelRole, titleLabel);

    descriptionLabel = new QLabel(formLayoutWidget);
    descriptionLabel->setObjectName("descriptionLabel");
    descriptionLabel->setText("Description :");
    formLayout->setWidget(3, QFormLayout::LabelRole, descriptionLabel);

    locationLabel = new QLabel(formLayoutWidget);
    locationLabel->setObjectName("locationLabel");
    locationLabel->setText("Location :");
    formLayout->setWidget(4, QFormLayout::LabelRole, locationLabel);


    // Display parameters edition

    dateStartEdit = new QDateTimeEdit(formLayoutWidget);
    dateStartEdit->setObjectName(QString::fromUtf8("dateStartEdit"));
    //dateStartEdit->setGeometry(QRect(150, 300, 194, 27));
    dateStartEdit->setDate(QDate(time.getYear(), time.getMonth(), time.getDay()));
    dateStartEdit->setTime(QTime(time.getHour()+1, 0, 0));
    formLayout->setWidget(0, QFormLayout::FieldRole, dateStartEdit);

    dateEndEdit = new QDateTimeEdit(formLayoutWidget);
    dateEndEdit->setObjectName(QString::fromUtf8("dateEndEdit"));
    //dateEndEdit->setGeometry(QRect(150, 300, 194, 27));
    dateEndEdit->setDate(QDate(time.getYear(), time.getMonth(), time.getDay()));
    dateEndEdit->setTime(QTime(time.getHour()+2, 0, 0));
    formLayout->setWidget(1, QFormLayout::FieldRole, dateEndEdit);

    titleEdit = new QLineEdit(formLayoutWidget);
    titleEdit->setObjectName(QString::fromUtf8("titleEdit"));
    formLayout->setWidget(2, QFormLayout::FieldRole, titleEdit);

    descriptionEdit = new QLineEdit(formLayoutWidget);
    descriptionEdit->setObjectName(QString::fromUtf8("descriptionEdit"));
    formLayout->setWidget(3, QFormLayout::FieldRole, descriptionEdit);

    locationEdit = new QLineEdit(formLayoutWidget);
    locationEdit->setObjectName("locationEdit");
    formLayout->setWidget(4, QFormLayout::FieldRole, locationEdit);


    QSpacerItem *horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
    formLayout->setItem(5, QFormLayout::SpanningRole, horizontalSpacer);

    buttonBox = new QDialogButtonBox(formLayoutWidget);
    buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
    buttonBox->setOrientation(Qt::Horizontal);
    buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
    formLayout->setWidget(6, QFormLayout::FieldRole, buttonBox);

    QObject::connect(this->buttonBox, SIGNAL(accepted()), this, SLOT(checkFields()));

}

void SlotDialog::setArgs(Time* dateStart, Time* dateEnd, string intitule, string description) {
    dateStartEdit->setDate(QDate(dateStart->getYear(), dateStart->getMonth(), dateStart->getDay()));
    dateStartEdit->setTime(QTime(dateStart->getHour(), 0, 0));
    dateEndEdit->setDate(QDate(dateEnd->getYear(), dateEnd->getMonth(), dateEnd->getDay()));
    dateEndEdit->setTime(QTime(dateEnd->getHour(), 0, 0));
    this->titleEdit->setText(QString(intitule.c_str()));
    this->descriptionEdit->setText(QString(description.c_str()));
}


SlotDialog::~SlotDialog()
{
    delete parent;

    delete frame;

    delete dateStartLabel;
    delete dateEndLabel;
    delete titleLabel;
    delete descriptionLabel;

    delete formLayoutWidget;
    delete formLayout;
    delete dateStartEdit;
    delete dateEndEdit;
    delete titleEdit;
    delete descriptionEdit;
    delete buttonBox;
}

void SlotDialog::checkFields() {
    qDebug() << "LOLILOL";
    if(titleEdit->text().isEmpty())
        QMessageBox::warning(this, "Error", "You must fill at least the title field");
    else
        emit acceptedAndOk();
}

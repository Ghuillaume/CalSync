#include "../../headers/View/DateDialog.hpp"

DateDialog::DateDialog ( QWidget* parent ): QDialog ( parent )
{
    this->parent = ( View* ) parent;

    this->setObjectName("Dialog");
    this->setWindowTitle("Choix de la date");
    this->resize(400, 300);
    
    buttonBox = new QDialogButtonBox(this);
    buttonBox->setObjectName("buttonBox");
    buttonBox->setGeometry(QRect(30, 250, 341, 32));
    buttonBox->setOrientation(Qt::Horizontal);
    buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
    
    calendarWidget = new QCalendarWidget(this);
    calendarWidget->setObjectName("calendarWidget");
    calendarWidget->setGeometry(QRect(40, 30, 312, 179));
    calendarWidget->setFirstDayOfWeek(Qt::Monday);
    
    Time *parentTime = this->parent->getTime();
    calendarWidget->setSelectedDate(QDate(parentTime->getYear(), parentTime->getMonth(), parentTime->getDay()));
}

void DateDialog::setWeek()
{
	QDate d = this->calendarWidget->selectedDate();
    this->parent->getTime()->setDate(0, 8, d.day(), d.month(), d.year());
	this->parent->getTime()->setWeek(this->parent->getTime()->getWeek());
	this->parent->setWeek();
	this->accept();
}

DateDialog::~DateDialog()
{
	delete buttonBox;
	delete calendarWidget;
}

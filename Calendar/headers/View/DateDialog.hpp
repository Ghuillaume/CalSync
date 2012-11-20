#ifndef _DATEDIALOG_HPP_
#define _DATEDIALOG_HPP_

#include <QtCore>
#include <QtGui>
#include <QWidget> 
#include <QDialog>
#include <QDate>

#include "View.hpp"
#include "../Model/Time.hpp"

class View;

class DateDialog: public QDialog
{ Q_OBJECT
    private:
        Time time;
        View *parent;

	    QCalendarWidget *calendarWidget;

    public:
    	QDialogButtonBox *buttonBox;
    
        DateDialog(QWidget* mainWindow);
       ~DateDialog();

    public slots:
	    void setWeek();
};

#endif

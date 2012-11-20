#ifndef _VIEW_HPP_
#define _VIEW_HPP_

#include <QMainWindow>
#include <QLabel>
#include <QtGui>

#include <iostream>
#include <sstream>

#include "../Model/common.h"
#include "../Model/Time.hpp"
#include "Model.hpp"
#include "DateDialog.hpp"
#include "SlotDialog.hpp"

class View: public QMainWindow
{ Q_OBJECT
    private:
        Time time;
        Model *model;

    public:
        View(Model *model);
       ~View();
	
	    Time *getTime();
	    Model *getModel();
	    
	    void setWeek();
	    void setSlot(const string &s, int row, int column);
	    
	    void updateFilter ();
    
	    // Main frame:
	    QWidget *mainFrame;
	    QVBoxLayout *mainLayout;
	
	    // Table:
	    QTableWidget *tableWidget;
	
	    // Date frame:
	    QFrame *dateFrame;
	    QHBoxLayout *dateLayout;
	    QPushButton *datePrevious;
	    QPushButton *dateSelect;
	    QPushButton *dateNext;
	
	    // Menubar:
	    QMenuBar *menubar;
	
	    QMenu *fileMenu;
	    QAction *newItem;
	    QAction *saveItem;
	    QAction *saveAsItem;
	    QAction *quitItem;
	    QAction *openItem;
	

    public slots:
        void display ();
	    void previousWeek();
	    void nextWeek();
};

#endif

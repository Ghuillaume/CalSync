#ifndef _VIEW_HPP_
#define _VIEW_HPP_

#include <QMainWindow>
#include <QLabel>
#include <QtGui>

#include <iostream>
#include <sstream>
#include <string>

#include "../Model/common.h"
#include "../Model/Time.hpp"
#include "../Model/Model.hpp"
#include "DateDialog.hpp"
#include "SlotDialog.hpp"

#define TOP_MARGIN 20
#define LEFT_MARGIN 20
#define TABLE_MARGIN 250
#define TABLE_WIDTH 770

class View: public QMainWindow
{
    Q_OBJECT

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

        
        // Table:
        //QTableWidget *tableWidget;
        QWidget *mainLayoutWidget;
        QVBoxLayout *mainLayout;
        QHBoxLayout *controlLayout;
        QPushButton *datePrevious;
        QLabel *currentWeek;
        QPushButton *dateNext;
        QListWidget *slotListWidget;


        // Menubar:
        QMenuBar *menubar;

        QMenu *fileMenu;
        QAction *newItem;
        QAction *saveItem;
        QAction *saveAsItem;
        QAction *quitItem;
        QAction *openItem;
    
    private:
        Time time;
        Model *model;
	

    public slots:
        void display ();
        void previousWeek();
        void nextWeek();
};

#endif

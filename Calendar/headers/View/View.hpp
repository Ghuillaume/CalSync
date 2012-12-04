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
#include "SlotActionDialog.hpp"
#include "SlotFrame.hpp"

#define TOP_MARGIN 10
#define LEFT_MARGIN 10
#define TABLE_MARGIN 250
#define TABLE_WIDTH 950
#define TABLE_HEIGHT 710

class View: public QMainWindow
{
    Q_OBJECT

    public:
        View(Model *model);
        ~View();
       
        Time *getTime();
        Model *getModel();
        int getFirstEventPosition();
        void updateDays();
        void setSlot(const string &s, int row, int column);

        void updateFilter ();

        // Menubar:
        QMenuBar *menubar;
        QMenu *fileMenu;
            QAction *newItem;
            QAction *saveItem;
            QAction *saveAsItem;
            QAction *quitItem;
            QAction *openItem;
        QMenu *editMenu;
            QAction *newSlotItem;
            QAction *settingsItem;
            QAction* changeKeyItem;
        QMenu* lolMenu;
            QAction* reloadItem;
            QAction* importItem;
            QAction* exportItem;
            
        // Start view buttons
        QWidget* horizontalLayoutWidgetNewModel;
        QHBoxLayout* horizontalLayoutNewModel;
        QPushButton* newEmptyModel;
        QPushButton* newModelFromLocal;
        QPushButton* newModelFromGoogle;
        
        // Main frame:
        QWidget *mainFrame;
        
        // Table:
        QWidget *mainLayoutWidget;
        QVBoxLayout *mainLayout;
        QHBoxLayout *controlLayout;
        QPushButton *datePrevious;
        QLabel *currentWeek;
        QPushButton *dateNext;
        //QListWidget *slotListWidget;
		//
		QTableWidget *tableWidget;
		//
		
		vector<Slot*> currentSlots;
		vector<SlotFrame*> currentButtons;
    
    private:
        Time time;
        Model *model;
        int firstEventPosition;
		
		void displaySlots();

    public slots:
        void display ();
        void previousWeek();
        void nextWeek();
};

#endif

#include "View.hpp"

View::View(Model *model) : QMainWindow(), time(8)
{
    this -> model = model;

	// Main window:
    this->setWindowTitle("Emploi du temps");
    this->resize(QSize(800, 400));

	// Main frame:
    mainFrame = new QWidget(this);
    this->setCentralWidget(mainFrame);
    mainFrame->setObjectName("mainFrame");
    
    mainLayout = new QVBoxLayout(mainFrame);
    mainLayout->setObjectName("mainLayout");

	// Table:
    tableWidget = new QTableWidget(mainFrame);
    mainLayout->addWidget(tableWidget);
    tableWidget->setObjectName("tableWidget");
    tableWidget->setSelectionMode(QAbstractItemView::NoSelection);
    
    tableWidget->setColumnCount(11);
    for ( int i = 0; i < 12; ++i )
    {
    	std::stringstream stream;
        stream << ( i > 1 ? "" : "0" ) << i + 8  << "h00"; 
    	
		QTableWidgetItem *columnHead = new QTableWidgetItem();
		tableWidget->setHorizontalHeaderItem(i, columnHead);
		columnHead->setText(stream.str().c_str());
    }
    
    tableWidget->setRowCount(6);
    tableWidget->verticalHeader()->setDefaultSectionSize(60);
    for ( int i = 0; i < 6; ++i )
    {
		QTableWidgetItem *rowHead = new QTableWidgetItem();
		tableWidget->setVerticalHeaderItem(i, rowHead);
    }
    
    for (int i = 0 ; i < 6 ; i++)
    {
	    for(int j = 0 ; j < 12 ; j++)
	    {
	        QLabel* q = new QLabel(tableWidget);
	        tableWidget->setCellWidget(i, j, q);
	    }
	}
    
	// Date frame:
    dateFrame = new QFrame(mainFrame);
    mainLayout->addWidget(dateFrame);
    dateFrame->setObjectName("dateFrame");
    dateFrame->setMinimumSize(QSize(0, 40));
    
    dateLayout = new QHBoxLayout(dateFrame);
    dateLayout->setObjectName("dateLayout");
    
    datePrevious = new QPushButton(dateFrame);
    datePrevious->setObjectName("datePrevious");
    dateLayout->addWidget(datePrevious);
    datePrevious->setText(QString::fromUtf8("Semaine précédente"));

    dateSelect = new QPushButton(dateFrame);
    dateSelect->setObjectName("dateSelect");
    dateLayout->addWidget(dateSelect);
    dateSelect->setText("Choix date");

    dateNext = new QPushButton(dateFrame);
    dateNext->setObjectName("dateNext");
    dateLayout->addWidget(dateNext);
    dateNext->setText("Semaine suivante");

    // Menubar:
    menubar = new QMenuBar(this);
    this->setMenuBar(menubar);
    menubar->setObjectName("menubar");
    menubar->setGeometry(QRect(0, 0, 800, 25));

    fileMenu = new QMenu(menubar);
    fileMenu->setObjectName("fileMenu");
    menubar->addAction(fileMenu->menuAction());
    fileMenu->setTitle("Fichier");
    
    newItem = new QAction(this);
    newItem->setObjectName("newItem");
    fileMenu->addAction(newItem);
    newItem->setText("Nouveau...");
    
    openItem = new QAction(this);
    openItem->setObjectName("openItem");
    fileMenu->addAction(openItem);
    openItem->setText("Ouvrir...");
    
    saveItem = new QAction(this);
    saveItem->setObjectName("saveItem");
    fileMenu->addAction(saveItem);
    saveItem->setText("Enregistrer");
    
    saveAsItem = new QAction(this);
    saveAsItem->setObjectName("saveAsItem");
    fileMenu->addAction(saveAsItem);
    saveAsItem->setText("Enregistrer sous...");
    
    quitItem = new QAction(this);
    quitItem->setObjectName("quitItem");
    fileMenu->addAction(quitItem);
    quitItem->setText("Quitter");
	
    this->time.setWeek(this->time.getWeek());
	this->setWeek();
}

Time* View::getTime()
{
    return &(this->time);    
}

Model* View::getModel()
{
    return this->model;    
}

void View::setWeek()
{
	string dayName[6] = { "Lundi", "Mardi", "Mercredi", "Jeudi", "Vendredi", "Samedi" };
    Time tmp = time;
	for (int i = 0; i < 6; i++)
	{
		stringstream stream;
		stream << dayName[i] << "\n" << tmp.getDate();
		tableWidget->verticalHeaderItem(i)->setText(stream.str().c_str());
        
		tmp.nextDay();
	}
}

void View::setSlot(const string &s, int row, int column)
{
    QLabel *w = (QLabel*) tableWidget -> cellWidget(row, column);
    w -> setText(QString::fromUtf8(s.c_str()));
}

void View::updateFilter ()
{
    this -> filterTypeChanged ( this -> filterType -> currentIndex () );
}

View::~View()
{
	delete newItem;
	delete saveItem;
	delete saveAsItem;
	delete quitItem;
	delete openItem;
	
	delete fileMenu;
	
	delete menubar;
	
	delete datePrevious;
	delete dateSelect;
	delete dateNext;
	delete dateLayout;
	delete dateFrame;
	
	// Destruction de tous les QLabels créés dynamiquement
    for (int i = 0 ; i < 6 ; i++)
	    for(int j = 0 ; j < 11 ; j++)
	        delete tableWidget->cellWidget(i, j);
	delete tableWidget;
	
	        	
	delete mainLayout;
	delete mainFrame;
}

void View::display()
{
    // Firstly:
    for (int i = 0 ; i < 6 ; i++)
	    for(int j = 0 ; j < 11 ; j++)
	        this -> setSlot("", i, j);

    // Secondly:
    Time nextWeek = this -> time;
    nextWeek.setWeek ( nextWeek.getWeek () + 1 );

    Slots *slots_ = this -> model -> getSlots();
    Slots::iterator iterator = slots_ -> begin();
    for ( ; iterator != slots_ -> end(); iterator++ )
    {
        if ( (*iterator) -> getTime () >= this -> time
            && (*iterator) -> getTime () < nextWeek )
        {
            int row = (*iterator) -> getTime ().getWeekDay ();
            int column = (*iterator) -> getTime ().getHour () - 8;
            
            stringstream stream;
            stream << (*iterator) -> getIntitule();
            setSlot(stream.str(), row, column);
        }
    }
}

void View::previousWeek()
{
	this->time.setWeek(this->time.getWeek() - 1);
	this->setWeek();
	this -> display ();
}

void View::nextWeek()
{
	this->time.setWeek(this->time.getWeek() + 1);
	this->setWeek();
	this -> display ();
}

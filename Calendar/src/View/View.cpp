#include "../../headers/View/View.hpp"

View::View(Model *model) : QMainWindow(), time((minute_t)8)
{
    this -> model = model;

	// Main window:
    this->setWindowTitle("Emploi du temps");
    this->resize(QSize(TABLE_MARGIN + TABLE_WIDTH + 20, 650));

	// Main frame:
    mainFrame = new QWidget(this);
    this->setCentralWidget(mainFrame);
    mainFrame->setObjectName("mainFrame");

	// Table:
    tableWidget = new QTableWidget(mainFrame);
    tableWidget->setObjectName("tableWidget");
    tableWidget->setSelectionMode(QAbstractItemView::NoSelection);
    tableWidget->setGeometry(QRect(TABLE_MARGIN, TOP_MARGIN, TABLE_WIDTH, 600));
    
    tableWidget->setColumnCount(7);
    for ( int i = 0; i < 7; ++i )
    {
        QTableWidgetItem *columnHead = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(i, columnHead);
    }
    
    tableWidget->setRowCount(24);
    tableWidget->verticalHeader()->setDefaultSectionSize(60);
    for ( int i = 0; i < 24; ++i )
    {
    	std::stringstream stream;
        stream << ( i > 1 ? "" : "0" ) << i  << "h00"; 
    	
        QTableWidgetItem *rowHead = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(i, rowHead);
        rowHead->setText(stream.str().c_str());
    }
    
    for (int i = 0 ; i < 24 ; i++)
    {
	    for(int j = 0 ; j < 7 ; j++)
	    {
	        QLabel* q = new QLabel(tableWidget);
	        tableWidget->setCellWidget(i, j, q);
	    }
	}
    
	// Control frame:
    controlFrame = new QFrame(mainFrame);
    controlFrame->setObjectName("controlFrame");
    controlFrame->setMinimumSize(QSize(0, 40));
    controlFrame->setGeometry(QRect(LEFT_MARGIN, TOP_MARGIN, TABLE_MARGIN - LEFT_MARGIN - 20, 600));
    
    controlLayout = new QVBoxLayout(controlFrame);
    controlLayout->setObjectName("dateLayout");
    
    datePrevious = new QPushButton(controlFrame);
    datePrevious->setObjectName("datePrevious");
    controlLayout->addWidget(datePrevious);
    datePrevious->setText(QString::fromUtf8("<<< Semaine précédente"));
    
    dateNext = new QPushButton(controlFrame);
    dateNext->setObjectName("dateNext");
    controlLayout->addWidget(dateNext);
    dateNext->setText(QString::fromUtf8("Semaine suivante >>>"));
    
    dateNext = new QPushButton(controlFrame);
    dateNext->setObjectName("dateNext");
    controlLayout->addWidget(dateNext);
    dateNext->setText(QString::fromUtf8("Importer depuis"));

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
    string dayName[7] = { "Lundi", "Mardi", "Mercredi", "Jeudi", "Vendredi", "Samedi", "Dimanche" };
    Time tmp = time;
    for (int i = 0; i < 7; i++)
    {
            stringstream stream;
            stream << dayName[i] << "\n" << tmp.getDate();
            tableWidget->horizontalHeaderItem(i)->setText(stream.str().c_str());

            tmp.nextDay();
    }
}

void View::setSlot(const string &s, int row, int column)
{
    QLabel *w = (QLabel*) tableWidget -> cellWidget(row, column);
    w -> setText(QString::fromUtf8(s.c_str()));
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
	delete dateNext;
	delete controlLayout;
	delete controlFrame;
	
	// Destruction de tous les QLabels créés dynamiquement
    for (int i = 0 ; i < 24 ; i++)
	    for(int j = 0 ; j < 7 ; j++)
	        delete tableWidget->cellWidget(i, j);
	delete tableWidget;
        
	delete mainFrame;
}

void View::display()
{
    // Firstly:
    for (int i = 0 ; i < 6 ; i++)
	    for(int j = 0 ; j < 11 ; j++)
	        this -> setSlot("", i, j);

    // Secondly:
    /*Time nextWeek = this -> time;
    nextWeek.setWeek ( nextWeek.getWeek () + 1 );

    Slot *slots_ = this -> model -> getSlots();
    Slot::iterator iterator = slots_ -> begin();
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
    }*/
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

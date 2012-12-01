#include "../../headers/View/View.hpp"

View::View(Model *model) : QMainWindow(), time(8)
{
    this -> model = model;

	// Main window:
    this->setWindowTitle("Emploi du temps");
    this->resize(QSize(TABLE_MARGIN + TABLE_WIDTH + 20, LEFT_MARGIN*2 + TABLE_HEIGHT));
	//this->setFixedSize(size());
    
        // Menubar:
    menubar = new QMenuBar(this);
    this->setMenuBar(menubar);
    menubar->setObjectName("menubar");
    menubar->setGeometry(QRect(0, 0, TABLE_MARGIN + TABLE_WIDTH + 20, 25));

    fileMenu = new QMenu(menubar);
    fileMenu->setObjectName("fileMenu");
    menubar->addAction(fileMenu->menuAction());
    fileMenu->setTitle("File");
    
        newItem = new QAction(this);
        newItem->setObjectName("newItem");
        fileMenu->addAction(newItem);
        newItem->setText("New...");

        openItem = new QAction(this);
        openItem->setObjectName("openItem");
        fileMenu->addAction(openItem);
        openItem->setText("Open...");

        saveItem = new QAction(this);
        saveItem->setObjectName("saveItem");
        fileMenu->addAction(saveItem);
        saveItem->setText("Save");

        saveAsItem = new QAction(this);
        saveAsItem->setObjectName("saveAsItem");
        fileMenu->addAction(saveAsItem);
        saveAsItem->setText("Save as...");

        quitItem = new QAction(this);
        quitItem->setObjectName("quitItem");
        fileMenu->addAction(quitItem);
        quitItem->setText("Quit");

    editMenu = new QMenu(menubar);
    editMenu->setObjectName("editMenu");
    menubar->addAction(editMenu->menuAction());
    editMenu->setTitle("Edit");

        newSlotItem = new QAction(this);
        newSlotItem->setObjectName("newSlotItem");
        editMenu->addAction(newSlotItem);
        newSlotItem->setText("Create an event");

        editSlotItem = new QAction(this);
        editSlotItem->setObjectName("newSlotItem");
        editMenu->addAction(editSlotItem);
        editSlotItem->setText("Edit an event");

        deleteSlotItem = new QAction(this);
        deleteSlotItem->setObjectName("deleteSlotItem");
        editMenu->addAction(deleteSlotItem);
        deleteSlotItem->setText("Delete an event");

        editMenu->addSeparator();

        settingsItem = new QAction(this);
        settingsItem->setObjectName("settingsItem");
        editMenu->addAction(settingsItem);
        settingsItem->setText("Settings..");

        /*changeKeyItem = new QAction(this);
        changeKeyItem->setObjectName("changeKeyItem");
        editMenu->addAction(changeKeyItem);
        changeKeyItem->setText("Change my API Key");*/


    lolMenu = new QMenu(menubar);
    lolMenu->setObjectName("lolMenu");
    menubar->addAction(lolMenu->menuAction());
    lolMenu->setTitle("LOL");

        importItem = new QAction(this);
        importItem->setObjectName("importItem");
        lolMenu->addAction(importItem);
        importItem->setText("Import an existing calendar");

        exportItem = new QAction(this);
        exportItem->setObjectName("exportItem");
        lolMenu->addAction(exportItem);
        exportItem->setText("Save my calendar online");

    menubar->setVisible(false);
  
    horizontalLayoutWidgetNewModel = new QWidget(this);
    horizontalLayoutWidgetNewModel->setObjectName(QString::fromUtf8("horizontalLayoutWidget"));
    horizontalLayoutWidgetNewModel->setGeometry(QRect(50, 190, TABLE_MARGIN + TABLE_WIDTH + 20 - 100, 200)); 
    horizontalLayoutNewModel = new QHBoxLayout(horizontalLayoutWidgetNewModel);
    horizontalLayoutNewModel->setObjectName(QString::fromUtf8("horizontalLayout"));
    horizontalLayoutNewModel->setContentsMargins(0, 0, 0, 0);
    
    newEmptyModel = new QPushButton(horizontalLayoutWidgetNewModel);
    newEmptyModel->setObjectName(QString::fromUtf8("newEmptyModel"));
    newEmptyModel->setMinimumSize(QSize(0, 80));
    newEmptyModel->setText("New Empty Calendar");
    horizontalLayoutNewModel->addWidget(newEmptyModel);
    
    newModelFromLocal = new QPushButton(horizontalLayoutWidgetNewModel);
    newModelFromLocal->setObjectName(QString::fromUtf8("newModelFromLocal"));
    newModelFromLocal->setMinimumSize(QSize(0, 80));
    newModelFromLocal->setText("New Calendar From Local File");
    horizontalLayoutNewModel->addWidget(newModelFromLocal);
    
    newModelFromGoogle = new QPushButton(horizontalLayoutWidgetNewModel);
    newModelFromGoogle->setObjectName(QString::fromUtf8("newModelFromGoogle"));
    newModelFromGoogle->setMinimumSize(QSize(0, 80));
    newModelFromGoogle->setText("New Calendar From Google");
    horizontalLayoutNewModel->addWidget(newModelFromGoogle);
    
    horizontalLayoutWidgetNewModel->setVisible(true);
    
    
	// Main frame:
    mainFrame = new QWidget(this);
    this->setCentralWidget(mainFrame);
    mainFrame->setObjectName("mainFrame");
    
    mainLayoutWidget = new QWidget(mainFrame);
    mainLayoutWidget->setObjectName(QString::fromUtf8("mainLayoutWidget"));
    mainLayoutWidget->setGeometry(QRect(LEFT_MARGIN, TOP_MARGIN, TABLE_WIDTH + 250, TABLE_HEIGHT));
    mainLayout = new QVBoxLayout(mainLayoutWidget);
    mainLayout->setObjectName(QString::fromUtf8("mainLayout"));
    mainLayout->setContentsMargins(0, 0, 0, 0);
    
    controlLayout = new QHBoxLayout();
    controlLayout->setObjectName("dateLayout");
    
    datePrevious = new QPushButton(mainLayoutWidget);
    datePrevious->setObjectName("datePrevious");
    controlLayout->addWidget(datePrevious);
    datePrevious->setText(QString::fromUtf8("<<< Semaine précédente"));
    
    currentWeek = new QLabel(mainLayoutWidget);
    currentWeek->setObjectName(QString::fromUtf8("currentWeek"));
    currentWeek->setAlignment(Qt::AlignCenter);
    controlLayout->addWidget(currentWeek);
    
    dateNext = new QPushButton(mainLayoutWidget);
    dateNext->setObjectName("dateNext");
    controlLayout->addWidget(dateNext);
    dateNext->setText(QString::fromUtf8("Semaine suivante >>>"));
    
    
    mainLayout->addLayout(controlLayout);
    
    
//    slotListWidget = new QListWidget(mainLayoutWidget);
//    slotListWidget->setObjectName(QString::fromUtf8("slotListWidget"));
//
//    mainLayout->addWidget(slotListWidget);
	
    //
	tableWidget = new QTableWidget(mainLayoutWidget);
	tableWidget-> setObjectName(QString::fromUtf8("tableWidget"));
    tableWidget->setSelectionMode(QAbstractItemView::NoSelection);
	
	tableWidget->setRowCount(7);
    tableWidget->verticalHeader()->setDefaultSectionSize(90);
	this->setWeek();
    
    tableWidget->setColumnCount(11);
    tableWidget->horizontalHeader()->setDefaultSectionSize(100);
	
    for ( int i = 0; i < 11; ++i )
    {
     std::stringstream stream;
        stream << ( i > 1 ? "" : "0" ) << i+8 << "h00";
    
        QTableWidgetItem *columnHead = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(i, columnHead);
        columnHead->setText(stream.str().c_str());
    }
	
	mainLayout->addWidget(tableWidget);
	//
	
	/**/
//	QPushButton *button = new QPushButton(QString("Test"), mainLayoutWidget);
//	button->setGeometry(98, 59, 100, 90);
//	button->setDisabled(TRUE);
//	
//	QPushButton *button2 = new QPushButton(QString("Test2"), mainLayoutWidget);
//	button2->setGeometry(98+100, 59, 100, 90);
//	button->setDisabled(TRUE);
	/**/
	
    mainFrame->setVisible(false);
        
    this->display();
}

Time* View::getTime()
{
    //return &(this->time);
    return this->model->getCurrentDate();
}

Model* View::getModel()
{
    return this->model;    
}

int View::getFirstEventPosition() {
    return this->firstEventPosition;
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

	delete mainFrame;
}

void View::setWeek()
{
    string dayName[7] = { "Lundi", "Mardi", "Mercredi", "Jeudi", "Vendredi", "Samedi", "Dimanche" };
    Time tmp = *(this->model->getCurrentDate());
	for (int i = 0; i < 7; i++)
    {
            stringstream stream;
            stream << dayName[i] << "\n" << tmp.getSimpleDate();
			QTableWidgetItem *rowHead = new QTableWidgetItem();
			tableWidget->setVerticalHeaderItem(i, rowHead);
			rowHead->setText(stream.str().c_str());
			
            tmp.nextDay();
    }
}

void View::display()
{	
    // Display current week 
    Time* curDate = this->model->getCurrentDate();
    string str = "Week " + convertInt(curDate->getWeek());
    currentWeek->setText(QApplication::translate("MainWindow", const_cast<char *>(str.c_str()), 0, QApplication::UnicodeUTF8));
	ListOfSlot l = this->model->getSlotList();
    ListOfSlot::iterator it = l.begin();
	bool firstSlotFound = FALSE;
	
	
	// Destroy pointers of currentButtons and clean vectors of current objects
	for(unsigned int i = 0; i < currentSlots.size(); i++) {
		delete currentButtons.at(i);
	}
	currentSlots.clear();
	currentButtons.clear();
    
    // Recherche du premier créneau correspondant à la semaine qu'on affiche
    int pos = 0;
	while (!firstSlotFound && it != l.end()) {
        if((*it)->getDateDebut()->getWeek() == this->model->getCurrentDate()->getWeek()
                && (*it)->getDateDebut()->getYear() == this->model->getCurrentDate()->getYear()) {
            this->firstEventPosition = pos;
            firstSlotFound = TRUE;
        }
		if (!firstSlotFound) {
        pos++;
		it++;
		}
    }
    
    // A partir du premier créneau, afficher tous les créneaux jusqu'à ce que la semaine ne corresponde plus
	bool newWeek = FALSE;
	while (!newWeek && it != l.end()) {
        if((*it)->getDateDebut()->getWeek() != this->model->getCurrentDate()->getWeek()
                || (*it)->getDateDebut()->getYear() != this->model->getCurrentDate()->getYear()) {
            newWeek = TRUE;
		}
		//this->slotListWidget->addItem( QString((*it)->toString().c_str()) );
		currentSlots.push_back(*it);
		
		if (!newWeek) {
			it++;
		}
    }
	
	this->displaySlots();
}

void View::previousWeek()
{
    this->model->previousWeek();
	this->setWeek();
    this->display();
}

void View::nextWeek()
{
    this->model->nextWeek();
	this->setWeek();
    this->display();
}

void View::displaySlots() {
	for(unsigned int i = 0; i < currentSlots.size(); i++) {
		int weekDay = (currentSlots.at(i))->getDateDebut()->getWeekDay();
		int hourStart = (currentSlots.at(i))->getDateDebut()->getHour();
		int minuteStart = (currentSlots.at(i))->getDateDebut()->getMinute();
		int hourEnd = (currentSlots.at(i))->getDateFin()->getHour();
		int minuteEnd = (currentSlots.at(i))->getDateFin()->getMinute();
		
		// Build of the event name (title + description)
		QString title((currentSlots.at(i))->getIntitule().c_str());
		title.append('\n');
		title.append((currentSlots.at(i))->getDescription().c_str());
		
		QPushButton *button = new QPushButton(title, mainLayoutWidget);
		int eventStartX = (hourStart - 8) * 100 + (minuteStart * 100 / 60) + 98;
		int eventStartY = weekDay * 90 + 59;
		
		int hourDuration = hourEnd - hourStart;
		int minuteDuration = 0;
		if ((minuteEnd - minuteStart) < 0) {
			minuteDuration = (60 + minuteEnd) - minuteStart;
			hourDuration--;
		} else {
			minuteDuration = minuteEnd - minuteStart;
		}
		int fullDuration = hourDuration * 100 + (minuteDuration*100/60);
		
		//xywh
		button->setGeometry( eventStartX, eventStartY, fullDuration, 90);
		button->setVisible(TRUE);
		button->setDisabled(TRUE);
		
		currentButtons.push_back(button);
	}
}
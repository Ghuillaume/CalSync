#include "../../headers/View/View.hpp"

View::View(Model *model) : QMainWindow(), time(8)
{
    this -> model = model;

	// Main window:
    this->setWindowTitle("Emploi du temps");
    this->resize(QSize(TABLE_MARGIN + TABLE_WIDTH + 20, 650));
    
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

        changePwdItem = new QAction(this);
        changePwdItem->setObjectName("changePwdItem");
        editMenu->addAction(changePwdItem);
        changePwdItem->setText("Change password");

        changeKeyItem = new QAction(this);
        changeKeyItem->setObjectName("changeKeyItem");
        editMenu->addAction(changeKeyItem);
        changeKeyItem->setText("Change my API Key");
    
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
    mainLayoutWidget->setGeometry(QRect(TABLE_MARGIN, TOP_MARGIN, TABLE_WIDTH, 600));
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
    
    
    slotListWidget = new QListWidget(mainLayoutWidget);
    slotListWidget->setObjectName(QString::fromUtf8("slotListWidget"));

    mainLayout->addWidget(slotListWidget);
    
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

void View::setWeek()
{
    /*string dayName[7] = { "Lundi", "Mardi", "Mercredi", "Jeudi", "Vendredi", "Samedi", "Dimanche" };
    Time tmp = time;
    for (int i = 0; i < 7; i++)
    {
            stringstream stream;
            stream << dayName[i] << "\n" << tmp.getDate();
            tableWidget->horizontalHeaderItem(i)->setText(stream.str().c_str());

            tmp.nextDay();
    }*/
}

void View::setSlot(const string &s, int row, int column)
{
    //QLabel *w = (QLabel*) tableWidget -> cellWidget(row, column);
    //w -> setText(QString::fromUtf8(s.c_str()));
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
	
	// Destruction de tous les QLabels créés dynamiquement
   /* for (int i = 0 ; i < 24 ; i++)
	    for(int j = 0 ; j < 7 ; j++)
	        delete tableWidget->cellWidget(i, j);
	delete tableWidget;*/
        
	delete mainFrame;
}

void View::display()
{
    
    // Display current week 
    Time* curDate = this->model->getCurrentDate();
    string str = "Week " + convertInt(curDate->getWeek());
    currentWeek->setText(QApplication::translate("MainWindow", const_cast<char *>(str.c_str()), 0, QApplication::UnicodeUTF8));
    
    // Clear slot list
    this->slotListWidget->clear();
    
    
    // Display slot of the current week
    ListOfSlot l = this->model->getSlotList();
    ListOfSlot::iterator it;
    
    // Recherche du premier créneau correspondant à la semaine qu'on affiche
    int pos = 0;
    for(it = l.begin() ; it != l.end() ; it++) {
        if((*it)->getDateDebut()->getWeek() == this->model->getCurrentDate()->getWeek()
                && (*it)->getDateDebut()->getYear() == this->model->getCurrentDate()->getYear()) {
            this->firstEventPosition = pos;
            break;
        }
        pos++;
    }
    
    // A partir du premier créneau, afficher tous les créneaux jusqu'à ce que la semaine ne corresponde plus
    for( ; it != l.end() ; it++) {
        if((*it)->getDateDebut()->getWeek() != this->model->getCurrentDate()->getWeek()
                || (*it)->getDateDebut()->getYear() != this->model->getCurrentDate()->getYear())
            break;
        
        this->slotListWidget->addItem( QString((*it)->toString().c_str()) );
    }
    
    
}

void View::previousWeek()
{
    this->model->previousWeek();
    this->display();
}

void View::nextWeek()
{
    this->model->nextWeek();
    this->display();
}

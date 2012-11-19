#include "Controller.hpp"

// Public :

Controller::Controller(Model *model, View *view)
{
    this -> model = model;
    this -> view = view;
    
    // Connexion signaux/slots de la vue
	QObject::connect(view -> quitItem, SIGNAL(activated()), view, SLOT(close()));
	
	QObject::connect(view -> filterType, SIGNAL(currentIndexChanged(int)), view, SLOT(filterTypeChanged(int)));

	QObject::connect(view -> dateNext, SIGNAL(clicked()), view, SLOT(nextWeek()));
	QObject::connect(view -> datePrevious, SIGNAL(clicked()), view, SLOT(previousWeek()));
	QObject::connect(view -> dateSelect, SIGNAL(clicked()), this, SLOT(selectWeek()));
	
	QObject::connect(view -> tableWidget, SIGNAL(cellDoubleClicked(int,int)), this, SLOT(createSlot(int,int)));
}

Controller::~Controller() { }

// Public slots :

void Controller::selectWeek()
{
	DateDialog *dialog = new DateDialog(view);
	QObject::connect(dialog->buttonBox, SIGNAL(accepted()), dialog, SLOT(setWeek()));
	QObject::connect(dialog->buttonBox, SIGNAL(rejected()), dialog, SLOT(reject()));
	dialog -> exec();
	delete dialog;
	view -> display ();
}

void Controller::createSlot(int row, int column)
{
    SlotDialog *dialog = new SlotDialog(view, row, column);
    QObject::connect(dialog->buttonBox, SIGNAL(accepted()), dialog, SLOT(createSlot()));
    QObject::connect(dialog->buttonBox, SIGNAL(rejected()), dialog, SLOT(reject()));
	dialog -> exec();
	delete dialog;
	view -> display ();
}

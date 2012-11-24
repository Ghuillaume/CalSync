#include "../../headers/Controler/Controler.hpp"
// Public :

Controler::Controler(Model *model, View *view)
{
    this -> model = model;
    this -> view = view;
    
    // Connexion signaux/slots de la vue
	QObject::connect(view -> quitItem, SIGNAL(activated()), view, SLOT(close()));

	QObject::connect(view -> datePrevious, SIGNAL(clicked()), view, SLOT(previousWeek()));
    QObject::connect(view -> dateNext, SIGNAL(clicked()), view, SLOT(nextWeek()));
	
	QObject::connect(view -> tableWidget, SIGNAL(cellDoubleClicked(int,int)), this, SLOT(createSlot(int,int)));
}

Controler::~Controler() { }

// Public slots :

void Controler::selectWeek()
{
	DateDialog *dialog = new DateDialog(view);
	QObject::connect(dialog->buttonBox, SIGNAL(accepted()), dialog, SLOT(setWeek()));
	QObject::connect(dialog->buttonBox, SIGNAL(rejected()), dialog, SLOT(reject()));
	dialog -> exec();
	delete dialog;
	view -> display ();
}

void Controler::createSlot(int row, int column)
{
    SlotDialog *dialog = new SlotDialog(view, row, column);
    QObject::connect(dialog->buttonBox, SIGNAL(accepted()), dialog, SLOT(createSlot()));
    QObject::connect(dialog->buttonBox, SIGNAL(rejected()), dialog, SLOT(reject()));
	dialog -> exec();
	delete dialog;
	view -> display ();
}

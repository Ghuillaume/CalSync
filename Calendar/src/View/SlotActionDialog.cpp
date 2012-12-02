#include "../../headers/View/SlotActionDialog.hpp"

SlotActionDialog::SlotActionDialog(QWidget *view) {
	this->view = (View*) view;

    this->setObjectName("ActionOnSlot");
    this->resize(300,50);
    this->setWindowTitle(QString::fromUtf8("Edit or delete slot"));
	
	horizontalLayout = new QHBoxLayout(this);
	
	editionButton = new QPushButton(this);
	editionButton->setText(QString("Edit"));
	
	deletionButton = new QPushButton(this);
	deletionButton->setText(QString("Delete"));
	
	cancelButton = new QPushButton(this);
	cancelButton->setText(QString("Cancel"));
	
	horizontalLayout->addWidget(editionButton);
	horizontalLayout->addWidget(deletionButton);
	horizontalLayout->addWidget(cancelButton);
}

SlotActionDialog::~SlotActionDialog() {
	delete editionButton;
	delete deletionButton;
	delete cancelButton;
	delete horizontalLayout;
}
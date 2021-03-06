#include "../../headers/View/SlotActionDialog.hpp"


/*
 * SlotActionDialog(QWidget *view, SlotFrame *frame)
 * SlotActionDialog constructor
 * Precondition : The string date is well-formed (dd-mm-yyyyThh:MM)
 * Postcondition : /
 */
SlotActionDialog::SlotActionDialog(QWidget *view, SlotFrame *frame) {
	this->view = (View*) view;
	this->frame = frame;

    this->setObjectName("ActionOnSlot");
    this->resize(300,50);
    this->setWindowTitle(QString::fromUtf8("Edit or delete slot"));
    this->setModal(true);
	
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

void SlotActionDialog::editSlot() {
    emit editSlotSignal(this->frame);
    this->accept();
}

void SlotActionDialog::deleteSlot() {
    emit deleteSlotSignal(this->frame);
    this->accept();
}
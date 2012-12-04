#include "SlotFrame.hpp"

SlotFrame::SlotFrame(QString title, QString description, Slot *slot): QFrame() {
    this->titleLabel = new QLabel(title, this);
    this->descriptionLabel = new QLabel(description, this);
	this->slot = slot;
    
    QPalette palette = this->palette();
    palette.setColor(backgroundRole(),QColor(245,245,245));
    this->setPalette(palette);
	this->setAutoFillBackground( true );
	this->setFrameStyle(QFrame::Panel | QFrame::Raised);
	this->setLineWidth(3);


    
    QVBoxLayout* layout = new QVBoxLayout();
    layout->setSpacing(0);
    layout->setContentsMargins(0,0,0,0);
    
    titleLabel->setAlignment(Qt::AlignCenter);
    descriptionLabel->setAlignment(Qt::AlignCenter);
    layout->addWidget(titleLabel);
    layout->addWidget(descriptionLabel);
    this->setLayout(layout);
    
    this->setMouseTracking(true);
}

SlotFrame::~SlotFrame() {
    delete titleLabel;
    delete descriptionLabel;
}

void SlotFrame::setSlot(Slot *slot) {
    this->slot = slot;
	this->titleLabel->setText(QString(this->slot->getIntitule().c_str()));
	this->descriptionLabel->setText(QString(this->slot->getDescription().c_str()));
}

Slot* SlotFrame::getSlot() {
    return this->slot;
}

void SlotFrame::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        emit slotClickedSignal(this);
    }
}

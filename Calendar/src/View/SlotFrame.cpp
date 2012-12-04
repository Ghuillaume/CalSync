#include "SlotFrame.hpp"

SlotFrame::SlotFrame(QString title, QString description): QFrame() {
    this->titleLabel = new QLabel(title, this);
    this->descriptionLabel = new QLabel(description, this);
	this->slot = NULL;
    
    QPalette palette = this->palette();
    palette.setColor(backgroundRole(),QColor(200,0,0));
    this->setPalette(palette);
    this->setFrameStyle(QFrame::StyledPanel);


    
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
}

Slot* SlotFrame::getSlot() {
    return this->slot;
}

void SlotFrame::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        emit slotClickedSignal(this);
    }
}

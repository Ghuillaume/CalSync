#include "SlotFrame.hpp"

SlotFrame::SlotFrame(QString title, QString description, Slot *slot): QFrame() {
    this->titleLabel = new QLabel(title, this);
    this->descriptionLabel = new QLabel(description, this);
    this->locationLabel = new QLabel(QString(slot->getLocation().c_str()), this);
	this->slot = slot;
    
    QPalette palette = this->palette();
    if(title.startsWith("TD"))
        palette.setColor(backgroundRole(),QColor(233,255,255));
    else if(title.startsWith("TP"))
        palette.setColor(backgroundRole(),QColor(255, 255, 211));
    else if(title.startsWith("CM"))
        palette.setColor(backgroundRole(),QColor(255,233,255));
    else
        palette.setColor(backgroundRole(),QColor(230,230,230));

    this->setPalette(palette);
	this->setAutoFillBackground( true );
	this->setFrameStyle(QFrame::Panel | QFrame::Raised);
    this->setLineWidth(3);

    QVBoxLayout* layout = new QVBoxLayout();
    layout->setSpacing(0);
    layout->setContentsMargins(0,0,0,0);
    
    titleLabel->setAlignment(Qt::AlignCenter);
    descriptionLabel->setAlignment(Qt::AlignCenter);
    locationLabel->setAlignment(Qt::AlignCenter);
    layout->addWidget(titleLabel);
    layout->addWidget(descriptionLabel);
    layout->addWidget(locationLabel);
    this->setLayout(layout);
    
    this->setMouseTracking(true);
}

SlotFrame::~SlotFrame() {
    delete titleLabel;
    delete descriptionLabel;
    delete locationLabel;
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

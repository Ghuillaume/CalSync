#include "../../headers/View/SlotDialog.hpp"

SlotDialog::SlotDialog(QWidget* parent, int row, int column):
    QDialog ( parent ),
    time    ()
{
    this->parent = (View*) parent;

    this->setObjectName("Dialog");
    this->resize(300, 162);
    this->setWindowTitle(QString::fromUtf8("Créer un nouveau créneau"));

    frame = new QWidget(this);
    frame->setObjectName("frame");
    frame->setGeometry(QRect(0, 10, 300, 150));
    
    layout = new QVBoxLayout(frame);
    layout->setObjectName("layout");
    
    label = new QLabel(frame);
    label->setObjectName("label");
    
    Time parentTime = *(this->parent->getTime());
    time.setDate (
        parentTime.getMinute  () + column,
        parentTime.getHour  () + column,
        parentTime.getDay   () + row,
        parentTime.getMonth (),
        parentTime.getYear  ()
    );

    stringstream stream;
    stream << "<b>Date :</b> "
           << ( time.getHour() > 9 ? "" : "0" )
           << time.getHour() << "h00, "
           << time.getDate ();
    label->setText(QString::fromStdString(stream.str()));
    layout->addWidget(label);

    
    buttonBox = new QDialogButtonBox(frame);
    buttonBox->setObjectName("buttonBox");
    buttonBox->setOrientation(Qt::Horizontal);
    buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

    layout->addWidget(buttonBox);
}

void SlotDialog::createSlot()
{
    //TODO : création du slot !!!!!
    this -> accept();
}

SlotDialog::~SlotDialog()
{
    delete buttonBox;
    delete label;
    delete layout;
    delete frame;
}


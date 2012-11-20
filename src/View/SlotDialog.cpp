#include "SlotDialog.hpp"

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

    room = new QComboBox(frame);
    room->setObjectName("room");
    room->clear();
    QStringList roomList;
    Rooms *rooms = this -> parent -> getModel() -> getRooms();
    Rooms::iterator roomIterator = rooms -> begin();
    for ( ; roomIterator != rooms -> end(); roomIterator++ )
    {
        stringstream roomStream;
        roomStream << "Bat. "
                   << (*roomIterator) -> getBuilding  () << ", salle "
                   << (*roomIterator) -> getNumber    ();
        roomList << QString::fromUtf8(roomStream.str().c_str());
        roomIDList << QString::fromStdString((*roomIterator) -> getID ());
    }
    room->insertItems(0, roomList);
    layout->addWidget(room);
    
    teacher = new QComboBox(frame);
    teacher->setObjectName("teacher");
    teacher->clear();
    Teachers *teachers = this -> parent -> getModel() -> getTeachers();
    Teachers::iterator teacherIterator = teachers -> begin();
    for ( ; teacherIterator != teachers -> end(); teacherIterator++ )
    {
        stringstream teacherStream;
        teacherStream << (*teacherIterator) -> getFirstname () << " "
                      << (*teacherIterator) -> getLastname  ();
        teacherList << QString::fromUtf8(teacherStream.str().c_str());
        teacherIDList << QString::fromStdString((*teacherIterator) -> getID ());
    }
    teacher->insertItems(0, teacherList);
    layout->addWidget(teacher);
    
    module = new QComboBox(frame);
    module->setObjectName("module");
    module->clear();
    QStringList moduleList;
    Modules *modules = this->parent -> getModel() -> getModules();
    Modules::iterator moduleIterator = modules -> begin();
    for ( ; moduleIterator != modules -> end(); moduleIterator++ )
    {
        moduleList << QString::fromUtf8((*moduleIterator) -> getName().c_str());
        moduleIDList << QString::fromStdString((*moduleIterator) -> getID ());
    }
    module->insertItems(0, moduleList);
    layout->addWidget(module);

    buttonBox = new QDialogButtonBox(frame);
    buttonBox->setObjectName("buttonBox");
    buttonBox->setOrientation(Qt::Horizontal);
    buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

    layout->addWidget(buttonBox);
}

void SlotDialog::createSlot()
{
    Slot *slot = new Slot (
        time,
        LECTURE,
        this -> parent -> getModel () -> getRoom    ( roomIDList   .at ( room    -> currentIndex () ).toStdString () ),
        this -> parent -> getModel () -> getModule  ( moduleIDList .at ( module  -> currentIndex () ).toStdString () ),
        this -> parent -> getModel () -> getTeacher ( teacherIDList.at ( teacher -> currentIndex () ).toStdString () )
    );
    
    try
    {
        Slot *existingSlot = this -> parent -> getModel () -> getSlotByDate ( time );
        this -> parent -> getModel () -> delSlot ( existingSlot );
    }
    catch ( runtime_error &re ) {}
    
    this -> parent -> getModel () -> addSlot ( slot );
    this -> accept();
}

SlotDialog::~SlotDialog()
{
    delete buttonBox;
    delete label;
    delete layout;
    delete frame;
}


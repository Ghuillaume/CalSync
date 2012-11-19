#ifndef _SLOTDIALOG_HPP_
#define _SLOTDIALOG_HPP_

#include <QtCore>
#include <QtGui>

#include <stdexcept>
#include <sstream>
#include <string>

#include "../types.hpp"
#include "Slot.hpp"
#include "View.hpp"

class View;

class SlotDialog: public QDialog
{ Q_OBJECT
    private:
        View *parent;
        Time time;

        QWidget *frame;
        QVBoxLayout *layout;
        
        QLabel      *label;
        QComboBox   *room;
        QStringList  roomList;
        QStringList  roomIDList;
        QComboBox   *teacher;
        QStringList  teacherList;
        QStringList  teacherIDList;
        QComboBox   *module;
        QStringList  moduleList;
        QStringList  moduleIDList;
    
    public:
        QDialogButtonBox *buttonBox;
        
        SlotDialog(QWidget *parent, int row, int column);
       ~SlotDialog();
    
    public slots:
        void createSlot();
};

#endif

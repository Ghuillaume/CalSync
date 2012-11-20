#ifndef _SLOTDIALOG_HPP_
#define _SLOTDIALOG_HPP_

#include <QtCore>
#include <QtGui>

#include <stdexcept>
#include <sstream>
#include <string>

#include "../Model/Slot.hpp"
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
    
    public:
        QDialogButtonBox *buttonBox;
        
        SlotDialog(QWidget *parent, int row, int column);
       ~SlotDialog();
    
    public slots:
        void createSlot();
};

#endif

#ifndef _SLOTACTIONDIALOG_HPP_
#define	_SLOTACTIONDIALOG_HPP_

#include <QtCore>
#include <QtGui>
#include <stdexcept>
#include <string>

#include "../Model/Slot.hpp"
#include "View.hpp"

class View;

class SlotActionDialog: public QDialog
{ Q_OBJECT
    private:
        View *view;
    
    public:
        QHBoxLayout* horizontalLayout;
		QPushButton *editionButton;
		QPushButton *deletionButton;
		QPushButton *cancelButton;
        
        SlotActionDialog(QWidget *view);
       ~SlotActionDialog();
};
#endif	


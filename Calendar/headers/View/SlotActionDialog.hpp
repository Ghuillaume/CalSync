#ifndef _SLOTACTIONDIALOG_HPP_
#define	_SLOTACTIONDIALOG_HPP_

#include <QtCore>
#include <QtGui>
#include <stdexcept>
#include <string>

#include "../Model/Slot.hpp"
#include "../View/SlotFrame.hpp"
#include "View.hpp"

class View;

class SlotActionDialog: public QDialog
{ Q_OBJECT
    private:
        View *view;
    
    public:
		SlotFrame *frame;
        QHBoxLayout* horizontalLayout;
		QPushButton *editionButton;
		QPushButton *deletionButton;
		QPushButton *cancelButton;
        
        SlotActionDialog(QWidget *view, SlotFrame *frame);
       ~SlotActionDialog();
	   
	public slots:
		void editSlot();
	
	signals:
		void editSlotSignal(SlotFrame*);
};
#endif	


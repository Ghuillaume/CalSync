/* 
 * File:   newfile.hpp
 * Author: yoros
 *
 * Created on 2 décembre 2012, 09:05
 */

#ifndef _NEWFILE_HPP_
#define	_NEWFILE_HPP_

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


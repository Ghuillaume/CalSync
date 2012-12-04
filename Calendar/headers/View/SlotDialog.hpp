#ifndef _SLOTDIALOG_HPP_
#define _SLOTDIALOG_HPP_

#include <QtCore>
#include <QtGui>

#include <stdexcept>
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

        QLabel      *dateStartLabel;
        QLabel      *dateEndLabel;
        QLabel      *titleLabel;
        QLabel      *descriptionLabel;
        QLabel      *locationLabel;
    
    public:
        QWidget *formLayoutWidget;
        QFormLayout *formLayout;
        QDateTimeEdit *dateStartEdit;
        QDateTimeEdit *dateEndEdit;
        QLineEdit *titleEdit;
        QLineEdit *descriptionEdit;
        QLineEdit *locationEdit;
        QDialogButtonBox *buttonBox;
        
        SlotDialog(QWidget *parent);
       ~SlotDialog();

        void setArgs(Time* dateStart, Time* dateEnd, string intitule, string description);

    public slots:
        void checkFields();

    signals:
        void acceptedAndOk();
};

#endif

#ifndef SETTINGSDIALOG_HPP
#define SETTINGSDIALOG_HPP


#include "View.hpp"

class View;

class SettingsDialog: public QDialog
{
    Q_OBJECT

    private:
        View *parent;
        QWidget *frame;

    public:
        SettingsDialog(QWidget *parent);
       ~SettingsDialog();

        QWidget *formLayoutWidget;
        QFormLayout *formLayout;

        QLabel* serviceLabel;
        QLabel* idCalendarLabel;
        QLabel* googleAuthLabel;
        QLabel* inputCalendarLabel;

        QPushButton* pwdButton;
        // selection box ?? pour service
        QLineEdit* idCalendarEdit;
        QPushButton* googleAuthButton;
        // selection box ?? pour inputcalendar

        QDialogButtonBox *buttonBox;
};

#endif // SETTINGSDIALOG_HPP

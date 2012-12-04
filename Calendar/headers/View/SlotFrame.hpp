#ifndef SLOTFRAME_HPP
#define	SLOTFRAME_HPP

#include <QtGui>
#include <QtCore>

#include "../Model/Slot.hpp"

class SlotFrame : public QFrame
{
    Q_OBJECT
    public:
        QLabel* titleLabel;
        QLabel* descriptionLabel;

        SlotFrame(QString title,QString description, Slot *slot);
        virtual ~SlotFrame();

        Slot* getSlot();
        void setSlot(Slot* slot);

        void mousePressEvent(QMouseEvent *event);

    signals:
        void slotClickedSignal(SlotFrame*);

    private:
        Slot *slot;
};

#endif	


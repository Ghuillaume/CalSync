#ifndef SLOTFRAME_HPP
#define	SLOTFRAME_HPP

#include <QtGui>
#include <QtCore>

#include "../Model/Slot.hpp"

class SlotFrame : public QFrame
{ Q_OBJECT
public:
    Slot *slot;
    QLabel* titleLabel;
    QLabel* descriptionLabel;
    
    SlotFrame(QString title,QString description);
    virtual ~SlotFrame();
    
    void mousePressEvent(QMouseEvent *event);
    
signals:
    void sigCreneauClicked(SlotFrame*);
};

#endif	


///

#include <QApplication>

#include "Model.hpp"
#include "Teacher.hpp"
#include "Group.hpp"
#include "Module.hpp"
#include "Room.hpp"
#include "View.hpp"
#include "../Controller/Controller.hpp"

int main ( int argc, char *argv[] )
{
    QApplication app(argc, argv);

    Model model;
    
    Teacher t("Alexandre", "Dikovsky");
    Teacher u("René", "Thoraval");
    model.addTeacher(&t);
    model.addTeacher(&u);
    
    Group g("602D");
    Group h("609E");
    model.addGroup(&g);
    model.addGroup(&h);
    
    Module m("S32I010", "Ping-pong");
    Module n("S32I020", "Poney");
    model.addModule(&m);
    model.addModule(&n);
    
    Room r("14", "48",  30);
    Room s( "1",  "A", 100);
    model.addRoom(&r);
    model.addRoom(&s);

    View view(&model);
    
    Controller controller(&model, &view);
    
	view.show();

    return app.exec();
}

///

///

#include <QApplication>

#include "View/View.hpp"
#include "Model/Model.hpp"
#include "Controller/Controller.hpp"


int main ( int argc, char *argv[] )
{
    QApplication app(argc, argv);

    Model model;
    View view(&model);
	Controller controller(&model, &view);
    
    view.show();
    return app.exec();
}

///

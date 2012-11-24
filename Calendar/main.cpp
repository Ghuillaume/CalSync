/*
 * File:   main.cpp
 * Author: guillaume
 *
 * Created on 20 novembre 2012, 20:48
 */

#include <iostream>
#include <QtGui/QApplication>
#include <QDebug>
#include <qt4/QtGui/qstyleoption.h>

using namespace std;

#include "headers/Model/Time.hpp"
#include "headers/Model/Model.hpp"
#include "headers/Controler/Controler.hpp"
#include "headers/View/View.hpp"

int main(int argc, char *argv[]) {

    QApplication app(argc, argv);
    
    Model *model = new Model();
    
    /**
     * ZONE DE TESTS
     * 
     */
    
    
    
    
    string label = "Test ";
    model->createSlot(new Time(0, 8, 20, 12, 2012), new Time(20, 9, 20, 12, 2012), label + "1");
    model->createSlot(new Time(0, 2, 23, 11, 2012), new Time(40, 9, 24, 11, 2012), label + "2");
    model->createSlot(new Time(0, 10, 20, 10, 2012), new Time(30, 9, 20, 10, 2012), label + "3");
    model->createSlot(new Time(0, 10, 20, 11, 2012), new Time(2, 9, 20, 11, 2012), label + "4");
    model->createSlot(new Time(0, 8, 25, 12, 2012), new Time(20, 9, 25, 12, 2012), label + "5");
    
    ListOfSlot l = model->getSlotList();
    for(ListOfSlot::iterator it = l.begin() ; it != l.end() ; it++) {
        cout << (*it)->toString() << endl;
    }
    cout << endl << endl;
    
    
    
    /**
     * FIN ZONE DE TESTS
     * 
     */

    View *view = new View(model);
    
    Controler *controler = new Controler(model, view);
    
    view->show();

    //return 0;
    return app.exec();
}


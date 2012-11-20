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

int main(int argc, char *argv[]) {

    QApplication app(argc, argv);
    
    Model *model = new Model();
    string label = "Test ";
    model->createSlot(new Time(oclock, 8, 20, 11, 2012), new Time(oclock, 9, 20, 11, 2012), label + "1");
    model->createSlot(new Time(oclock, 2, 23, 11, 2012), new Time(oclock, 9, 24, 11, 2012), label + "2");
    model->createSlot(new Time(oclock, 10, 20, 11, 2012), new Time(oclock, 9, 20, 11, 2012), label + "3");
    model->createSlot(new Time(oclock, 10, 20, 11, 2012), new Time(oclock, 9, 20, 11, 2012), label + "4");
    
    ListOfSlot l = model->getSlotList();
    for(ListOfSlot::iterator it = l.begin() ; it != l.end() ; it++) {
        cout << (*it)->toString() << endl;
    }


    //return app.exec();
}


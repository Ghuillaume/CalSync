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
#include "headers/Controler/Config.hpp"
#include "headers/Controler/md5.hpp"
#include "headers/View/View.hpp"


int main(int argc, char *argv[]) {

    QApplication app(argc, argv);

    Config *config = new Config();
    Model *model = new Model();
    View *view = new View(model);
    Controler *controler = new Controler(model, view, config);

    view->show();

    //return 0;
    return app.exec();
}


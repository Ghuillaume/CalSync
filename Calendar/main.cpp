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
#include "headers/Controller/Controller.hpp"
#include "headers/Controller/Config.hpp"
#include "headers/Controller/md5.hpp"
#include "headers/View/View.hpp"


int main(int argc, char *argv[]) {

    QApplication app(argc, argv);

    Config *config = new Config();
    Model *model = new Model();
    View *view = new View(model);
    Controller *controller = new Controller(model, view, config);

    view->show();

    return app.exec();
}


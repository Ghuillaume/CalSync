/*
 * File:   main.cpp
 * Author: yoros
 *
 * Created on 18 novembre 2012, 10:16
 */

#include "../../Calendar.core/headers/Time.h"
#include <iostream>

using namespace std;

//#include <QtGui/QApplication>
/*
int main(int argc, char *argv[]) {
	// initialize resources, if needed
	// Q_INIT_RESOURCE(resfile);

	QApplication app(argc, argv);

	// create and show your widgets here

	return app.exec();
}
*/

int main() {
	Time* time = new Time();
	time->setDate(oclock, 12, 18, 11, 2012);
	cout << time->getDate() << endl;
}
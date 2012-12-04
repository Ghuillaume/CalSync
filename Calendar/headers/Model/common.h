/* 
 * File:   common.h
 * Author: e094326d
 *
 * Created on 18 novembre 2012, 10:34
 */

#ifndef COMMON_H
#define	COMMON_H


using namespace std;

#include <string>
#include <cstdlib>
#include <stdlib.h>
#include <cstring>
#include <set>
#include <iostream>
#include <QDebug>

#include "Slot.hpp"
#include "Slot.hpp"

typedef std::vector<std::string> ListOfString;

class Slot;
class Time;
class Model;
class Controller;

std::string convertInt(int number);

static ListOfString explode(const std::string& str, const char& delimiter)
{
    std::istringstream split(str);
    std::vector<std::string> tokens;
    for (std::string each; std::getline(split, each, delimiter); tokens.push_back(each));
    return tokens;
}

#endif	/* COMMON_H */

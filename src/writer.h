#ifndef WRITER_H
#define WRITER_H

#include <iostream>
#include <fstream>
#include <list>
#include "rule.h"

using namespace std;

enum OutputType {
    CSV,
    TEXT,
};

class Writer {
    static void write(ofstream &, map<int, list<Rule> >);
};

#endif

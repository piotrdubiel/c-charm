#ifndef WRITER_H
#define WRITER_H

#include <iostream>
#include <fstream>
#include "rule.h"
:wa

using namespace std;

enum OutputType {
    CSV,
    TEXT,
};

class Writer {
    static void write(ofstream &, map<int, list<Rule> >);
};

#endif

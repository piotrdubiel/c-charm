#ifndef WRITER_H
#define WRITER_H

#include <iostream>
#include <fstream>
#include "iset.h"

using namespace std;

enum OutputType {
    CSV,
    TEXT,
};

class Writer {
    static void write(ofstream &, vector<ISet*>);
};

#endif

#ifndef TEXT_WRITER_H
#define TEXT_WRITER_H

#include <iostream>
#include <fstream>
#include <map>
#include <list>
#include "rule.h"

//#include "writer.h"

class TextWriter {
public:
    static void write(ofstream &, map<int, list<Rule> >);
};

#endif

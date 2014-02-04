#ifndef CSV_WRITER_H
#define CSV_WRITER_H

#include <iostream>
#include <fstream>
#include <map>
#include <list>
#include "rule.h"
#include "dataset.h"

//#include "writer.h"

class CsvWriter {
public:
    static void write(ostream &, map<int, list<Rule> >, DataSet*);
};

#endif

#ifndef CHARM_H
#define CHARM_H

#include <list>
#include <deque>
#include "dataset.h"
#include "rule.h"
#include "graph.h"

using namespace std;

class Charm {

public:
    Charm(const DataSet &, int);
    list<Rule> get_rules(const DataSet &);
    void get_close_sets(int);

private:
    const DataSet & data_set; 
    int class_identifier;
    Graph * graph;


};

#endif

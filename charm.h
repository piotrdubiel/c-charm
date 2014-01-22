#ifndef CHARM_H
#define CHARM_H

#include <list>
#include <deque>
#include "dataset.h"
#include "rule.h"
#include "graph.h"
#include "set.h"

using namespace std;

class Charm {

public:
    Charm(const DataSet &, int);
    ~Charm();
    list<Rule> get_rules(const DataSet &);
    void get_close_sets(int);

private:
    const DataSet & data_set; 
    int class_identifier;
    vector<Set*> close_sets;
    Graph * graph;
    int min_sup;

    Node* create_node(vector<int> items);
	Node* create_node(Set *);
    void extend(Node*);
    void check_property(Node*, Node*, Node*);
};

#endif

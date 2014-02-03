#ifndef CHARM_H
#define CHARM_H

#include <list>
#include <deque>
#include "dataset.h"
#include "rule.h"
#include "graph.h"
#include "set.h"
#include "hashtable.h"

using namespace std;

class Charm {

public:
    Charm(DataSet *, int, int);
    Charm(DataSet *, int);
    ~Charm();
    vector<ISet*> get_close_sets();

private:
    DataSet* data_set; 
    int class_identifier;
    Graph * graph;
    int min_sup;

    HashTable hashes;

    Node* create_node(vector<int> items);
	Node* create_node(Set *);
    void extend(Node*);
    Node* check_property(Node*, Node*, Node*);
};

#endif

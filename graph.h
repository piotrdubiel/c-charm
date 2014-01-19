#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include "set.h"

using namespace std;

class Node {
    int first_class_id;
    bool single_class;


    int support;

    Set* set;

    Node* parent;
    vector<Node*> children;

public:
    Node(Set*);
    void set_parent(Node* parent);
    bool is_subset(Node *) const;

};

class Graph {
    
};
#endif

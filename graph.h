#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <stdio.h>
#include "set.h"

using namespace std;

class Node {
public:
    Set* set;

    Node* parent;
    vector<Node*> children;

    Node(Set*);
    ~Node();
    void set_parent(Node* parent);
    bool is_subset(Node *) const;
    void add_child(Node*);
    void free();

};

class Graph {
public:
    Node* root;
    Graph(): root(NULL) {};
    ~Graph() { delete root; };
    void add_node(Node *, Node *);
	void delete_node(Node*);
};
#endif

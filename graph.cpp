#include "graph.h"

#include <cmath>
#include <iostream>

Node::Node(Set * s): set(s)
{
}

Node::~Node() {
    if (set != NULL) {
        delete set;
    }
    vector<Node*>::iterator it;
    for (it=children.begin(); it!=children.end(); ++it) {
        delete *it;
    }
}

void Node::set_parent(Node * parent) {
    this->parent = parent;
}

void Node::add_child(Node * node) {
    children.push_back(node);
}

void Graph::add_node(Node * node, Node * parent) {
    if (node == NULL) return;
    if (root == NULL) {
        root = node;
    }
    else {
        node->set_parent(parent);
        parent->add_child(node);
    }
}

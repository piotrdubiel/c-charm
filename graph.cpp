#include "graph.h"

#include <cmath>
#include <iostream>

Node::Node(Set * s): set(s)
{
}

void Node::set_parent(Node * parent) {
    this->parent = parent;
}

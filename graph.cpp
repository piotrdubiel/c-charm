#include "graph.h"

#include <cmath>
#include <iostream>
#include <algorithm>
#include <stdio.h>

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

void Node::free() {
    if (set != NULL) {
        delete set;
        set = NULL;
    }
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

void Graph::delete_node(Node* node) {
	vector<Node*> & children = node->parent->children;
	children.erase(find(children.begin(), children.end(), node));
	node->parent = NULL;
	delete node;
}

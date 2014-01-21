#include "charm.h"

#include <algorithm>

Charm::Charm(const DataSet & data_set, int class_identifier):
    data_set(data_set),
    class_identifier(class_identifier)
{

}


Charm::~Charm() {
    delete graph;
}

void Charm::get_close_sets(int min_sup) {
    this->min_sup = min_sup;
    graph = new Graph();

    graph->root = create_node(vector<int>());

    vector<int> ids = data_set.get_identifiers(class_identifier);
    vector<int>::iterator it;
    for (it=ids.begin(); it!=ids.end(); ++it) {
        vector<int> items;
        items.push_back(*it);
        graph->add_node(create_node(items), graph->root);
    }

    extend(graph->root);
}


Node* Charm::create_node(vector<int> items) {
    vector<int> tids = data_set.get_tids(items);
    if (tids.size() > min_sup) {
        Set* set = new Set(tids, items);
        Node* node = new Node(set);

        vector<int>::iterator it;
        int first_class = data_set.get_transaction(tids[0])[class_identifier];
        bool single_class = true;
        for (it=++tids.begin(); it!=tids.end(); ++it) {
            vector<int> transaction = data_set.get_transaction(*it);
            if (transaction[class_identifier] != first_class) {
                single_class = false;
                break;
            }
        }
        node->first_class_id = first_class;
        node->single_class = single_class;
        cout << "Node with class " << first_class << " has single class " << single_class << endl;
        return node;
    }
    else {
        cout << "Node not added" << endl;
        return NULL;
    }
}

void Charm::extend(Node * parent) {
    vector<Node*>::iterator it;
    for (it=parent->children.begin(); it!=parent->children.end(); ++it) {
        vector<Node*>::iterator j;
        for (j=it+1; j!=parent->children.end(); ++j) {
            vector<int> items;
            set_union((*it)->set->identifiers.begin(),
                    (*it)->set->identifiers.end(),
                    (*j)->set->identifiers.begin(),
                    (*j)->set->identifiers.end(),
                    items.begin());

            vector<int> tids;
            set_intersection((*it)->set->transactions.begin(),
                    (*it)->set->transactions.end(),
                    (*j)->set->transactions.begin(),
                    (*j)->set->transactions.end(),
                    tids.begin());

            if (tids.size() > min_sup) {
                Set * set = new Set(items, tids);
                //Node * candidate = create_node();
            }
        }
    }
}

Node* Charm::property(Node * a, Node * b) {
}

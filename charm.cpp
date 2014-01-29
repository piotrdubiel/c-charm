#include "charm.h"

#include <algorithm>
#include <iterator>

Charm::Charm(DataSet * d, int cls, int sup):
    data_set(d),
    class_identifier(cls),
    min_sup(sup)
{

}


Charm::~Charm() {
    delete graph;
    delete data_set;
}

vector<ISet*> Charm::get_close_sets(int min_sup) {
    this->min_sup = min_sup;
    graph = new Graph();

    graph->root = create_node(vector<int>());

    vector<int> ids = data_set->get_identifiers(class_identifier);
    vector<int>::iterator it;
    for (it=ids.begin(); it!=ids.end(); ++it) {
        vector<int> items;
        items.push_back(*it);
        graph->add_node(create_node(items), graph->root);
    }
    hashes.insert(graph->root->set);
    extend(graph->root);
    return hashes.content();
}


Node* Charm::create_node(vector<int> items) {
    vector<int> tids = data_set->get_tids(items);
    if (tids.size() >= min_sup) {
        Set* set = new Set(items, tids);
        Node* node = new Node(set);

        if (tids.size() > 0) {
            vector<int>::iterator it;
            int first_class = data_set->get_transaction(tids[0])[class_identifier];
            bool single_class = true;
            for (it=++tids.begin(); it!=tids.end(); ++it) {
                vector<int> transaction = data_set->get_transaction(*it);
                if (transaction[class_identifier] != first_class) {
                    single_class = false;
                    break;
                }
            }
            node->set->first_class_id = first_class;
            node->set->single_class = single_class;
        }
        return node;
    }
    else {
        return NULL;
    }
}

Node* Charm::create_node(Set * set) {
    if (set->support() >= min_sup) {
        Node* node = new Node(set);

        if (set->support() > 0) {
            vector<int>::iterator it;
            int first_class = data_set->get_transaction(set->transactions[0])[class_identifier];
            bool single_class = true;
            for (it=++set->transactions.begin(); it!=set->transactions.end(); ++it) {
                vector<int> transaction = data_set->get_transaction(*it);
                if (transaction[class_identifier] != first_class) {
                    single_class = false;
                    break;
                }
            }
            node->set->first_class_id = first_class;
            node->set->single_class = single_class;
        }
        return node;
    }
    else {
        return NULL;
    }
}

void Charm::extend(Node * parent) {
    vector<Node*>::iterator it;
    for (it=parent->children.begin(); it!=parent->children.end(); ++it) {
        vector<Node*>::iterator j;
        vector<Node*> to_delete;
        for (j=it; j!=parent->children.end(); ++j) {
            if (it == j) continue;
            vector<int> items;
            set_union((*it)->set->identifiers.begin(),
                    (*it)->set->identifiers.end(),
                    (*j)->set->identifiers.begin(),
                    (*j)->set->identifiers.end(),
                    back_inserter(items));

            vector<int> tids;
            set_intersection((*it)->set->transactions.begin(),
                    (*it)->set->transactions.end(),
                    (*j)->set->transactions.begin(),
                    (*j)->set->transactions.end(),
                    back_inserter(tids));

            if (tids.size() >= min_sup) {
                Set * set = new Set(items, tids);
                Node * candidate = create_node(set);

                if (candidate != NULL) {
                    Node * d = check_property(*it, *j, candidate);
                    if (d != NULL) {
                        to_delete.push_back(d);
                    }
                }
            }
        }

        vector<Node*>::iterator deleter;
        for (deleter=to_delete.begin(); deleter!=to_delete.end(); ++deleter) {
            graph->delete_node(*deleter);
        }

        hashes.insert((*it)->set);

        if (!(*it)->children.empty()) {
            extend(*it);	
        }
    }
}

Node* Charm::check_property(Node * a, Node * b, Node* candidate) {
    if (a->set == b->set) {
        a->set->identifiers = candidate->set->identifiers;
        delete candidate;
        return b;
    }
    else if (a->set->is_subset_of(*b->set)) {
        a->set->identifiers = candidate->set->identifiers;
        delete candidate;
    }
    else if (b->set->is_subset_of(*a->set)) {
        graph->add_node(candidate, a);
        return b;
    }
    else {
        graph->add_node(candidate, a);
    }
    return NULL;
}

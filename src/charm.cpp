#include "charm.h"

#include <algorithm>
#include <iterator>
#include <deque>

Charm::Charm(DataSet * d, int cls, int sup):
    data_set(d),
    class_identifier(cls),
    min_sup(sup)
{}

Charm::Charm(DataSet * d, int sup):
    data_set(d),
    min_sup(sup)
{
    class_identifier = d->last_attribute();
}

Charm::~Charm() {
    delete data_set;
}

vector<ISet*> Charm::get_close_sets() {
    graph = new Graph();

    graph->root = create_node(vector<int>());

    vector<int> ids = data_set->get_identifiers(class_identifier);
    deque<Node*> queue;
    vector<int>::iterator it;
    for (it=ids.begin(); it!=ids.end(); ++it) {
        vector<int> items;
        items.push_back(*it);
        Node * node = create_node(items);
        graph->add_node(node, graph->root);
    }

    queue.push_back(graph->root);
    while (!queue.empty()) {
        Node* parent = queue.front();
        queue.pop_front();

        vector<Node*>::iterator it;
        for (it=parent->children.begin(); it!=parent->children.end(); ++it) {
            if ((*it)->set->support() < min_sup) continue;
            vector<Node*>::iterator j;
            vector<Node*> to_delete;
            for (j=it; j!=parent->children.end(); ++j) {
                if ((*j)->set->support() < min_sup) continue;
                if (it == j) continue;
                vector<int> items;
                items.reserve((*it)->set->identifiers.size() + (*j)->set->identifiers.size());
                set_union((*it)->set->identifiers.begin(),
                        (*it)->set->identifiers.end(),
                        (*j)->set->identifiers.begin(),
                        (*j)->set->identifiers.end(),
                        back_inserter(items));

                vector<int> tids;
                tids.reserve((*it)->set->transactions.size() + (*j)->set->transactions.size());
                set_intersection((*it)->set->transactions.begin(),
                        (*it)->set->transactions.end(),
                        (*j)->set->transactions.begin(),
                        (*j)->set->transactions.end(),
                        back_inserter(tids));

                if (((int)tids.size()) >= min_sup) {
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
                queue.push_front(*it);
            }

        }

        hashes.insert(parent->set);
        parent->free();
    }
    delete graph;
    return hashes.content();
}


Node* Charm::create_node(vector<int> items) {
    vector<int> tids = data_set->get_tids(items);
    Set* set = new Set(items, tids);
    return create_node(set);
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

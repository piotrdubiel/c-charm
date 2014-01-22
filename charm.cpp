#include "charm.h"

#include <algorithm>
#include <iterator>

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
        Set* set = new Set(items, tids);
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

Node* Charm::create_node(Set * set) {
	if (set->transactions.size() > min_sup) {
        Node* node = new Node(set);

        vector<int>::iterator it;
		int first_class = data_set.get_transaction(set->transactions[0])[class_identifier];
        bool single_class = true;
        for (it=++set->transactions.begin(); it!=set->transactions.end(); ++it) {
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

            if (tids.size() > min_sup) {
                Set * set = new Set(items, tids);
                Node * candidate = create_node(set);

				if (candidate != NULL) {
					check_property(*it, *j, candidate);
				}
            }
        }

		if (!(*it)->children.empty()) {
			extend(*it);	
		}
		//delete (*it)->set;
    }
}

void Charm::check_property(Node * a, Node * b, Node* candidate) {
	if (a->set == b->set) {
		graph->delete_node(b);
		a->set->identifiers = candidate->set->identifiers;
		delete candidate;
	}
	else if (a->set->is_subset_of(*b->set)) {
		a->set->identifiers = candidate->set->identifiers;
		delete candidate;
	}
	else if (b->set->is_subset_of(*a->set)) {
		graph->delete_node(b);
		graph->add_node(candidate, a);
	}
	else {
		graph->add_node(candidate, a);
	}
}

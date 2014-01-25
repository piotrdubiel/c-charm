#include "hashtable.h"

void HashTable::insert(Set * n) {
    int hash = 0;
    vector<int>::iterator it;
    for (it=n->transactions.begin(); it != n->transactions.end(); ++it) {
        hash += *it + 1;
    }
    cout << "Sum: " << hash << endl;
    hash %= MOD;

    cout << "Hash: " << hash << endl;
    list<Set *> addition;
    addition.push_back(new Set(*n));
    pair<map<int,list<Set*> >::iterator,bool> ret = hash_map.insert(pair<int, list<Set*> >(hash, addition));
    if (ret.second == false) {
        bool can_add = true;
        list<Set*>::iterator lit;
        for (lit=ret.first->second.begin(); lit!=ret.first->second.end(); ++lit) {
            if (n->is_subsumed(**lit)) {
                can_add = false;
                cout << "Not added" << endl;
                break;
            }
        }

        if (can_add) {
            cout << "Added" << endl;
            ret.first->second.push_back(new Set(*n));
        }
    }

    //tmp.push_back(new Set(*n));
}

vector<Set*> HashTable::content() const {
    vector<Set*> result;
    map<int, list<Set*> >::const_iterator it;
    for (it=hash_map.begin(); it!=hash_map.end(); ++it) {
        result.insert(result.end(), it->second.begin(), it->second.end());
    }
    return result;
}

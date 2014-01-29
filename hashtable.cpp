#include "hashtable.h"

void HashTable::insert(Set * n) {
    int hash = 0;
    vector<int>::iterator it;
    for (it=n->transactions.begin(); it != n->transactions.end(); ++it) {
        hash += *it + 1;
    }
#ifdef DEBUG
    cout << "Sum: " << hash << endl;
#endif
    hash %= MOD;
#ifdef DEBUG
    cout << "Hash: " << hash << endl;
#endif

    ISet * candidate = new ISet(*n);
    list<ISet *> addition;
    addition.push_back(candidate);
    pair<map<int,list<ISet*> >::iterator,bool> ret = hash_map.insert(pair<int, list<ISet*> >(hash, addition));
    if (ret.second == false) {
        bool can_add = true;
        list<ISet*>::iterator lit;
        for (lit=ret.first->second.begin(); lit!=ret.first->second.end(); ++lit) {
            if (candidate->is_subsumed(**lit)) {
                can_add = false;
#ifdef DEBUG
                cout << "Not added" << endl;
#endif
                break;
            }
        }

        if (can_add) {
#ifdef DEBUG
            cout << "Added" << endl;
#endif
            ret.first->second.push_back(candidate);
        }
    }

}

vector<ISet*> HashTable::content() const {
    vector<ISet*> result;
    map<int, list<ISet*> >::const_iterator it;
    for (it=hash_map.begin(); it!=hash_map.end(); ++it) {
        result.insert(result.end(), it->second.begin(), it->second.end());
    }
    return result;
}
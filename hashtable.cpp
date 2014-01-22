#include "hashtable.h"

void HashTable::insert(Set * n) {
    int hash = 0;
    vector<int>::iterator it;
    for (it=n->transactions.begin(); it != n->transactions.end(); ++it) {
        hash += *it;
    }
    cout << "Sum: " << hash <<endl;
    hash %= MOD;
    cout << "Hash: " << hash << endl;

    //list<Set *>& bucket = hash_map[hash];


    tmp.push_back(new Set(*n));
}

vector<Set*> HashTable::content() {
    return tmp;
}

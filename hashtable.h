#ifndef HASHTABLE_H
#define HASHTABLE_H

#ifndef MOD
#define MOD 37247
#endif

#include <map>
#include <list>
#include <vector>
#include <iostream>
#include "set.h"
#include "iset.h"
#include "graph.h"

using namespace std;

class HashTable {
private:
    map<int, list<ISet*> > hash_map;

public:
    void insert(Set*);
    vector<ISet*> content() const;
};

#endif

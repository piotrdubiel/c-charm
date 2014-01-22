#ifndef HASHTABLE_H
#define HASHTABLE_H

#ifndef MOD
#define MOD 123
#endif

#include <map>
#include <list>
#include <vector>
#include <iostream>
#include "set.h"
#include "graph.h"

using namespace std;

class HashTable {
private:
    map<int, list<Set *> > hash_map;
    vector<Set*> tmp;

public:
    void insert(Set*);
    vector<Set*> content();
};

#endif

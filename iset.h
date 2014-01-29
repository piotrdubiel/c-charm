#ifndef ISET_H
#define ISET_H

#include <vector>
#include "set.h"

using namespace std;

class ISet {
public:
    ISet(const Set &);
    
    vector<int> identifiers;
    int sup;
    int first_class_id;
    bool single_class;

    bool is_subsumed(const ISet&);
	bool operator==(const ISet&);

    int support() const;
};

#endif

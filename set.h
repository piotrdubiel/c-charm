#ifndef SET_H
#define SET_H

#include <vector>

using namespace std;

class Set {
public:
    vector<int> identifiers;
    vector<int> transactions;

    int first_class_id;
    bool single_class;

    Set(vector<int>, vector<int>);
    Set(const Set&);

	bool is_subset_of(const Set&);

    bool is_subsumed(const Set&);
	bool operator==(const Set&);

    int support() const;
};

#endif

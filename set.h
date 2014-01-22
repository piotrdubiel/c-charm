#ifndef SET_H
#define SET_H

#include <vector>

using namespace std;

class Set {
public:
    vector<int> identifiers;
    vector<int> transactions;

    Set(vector<int>, vector<int>);

	bool is_subset_of(const Set&);

	bool operator==(const Set&);
};

#endif

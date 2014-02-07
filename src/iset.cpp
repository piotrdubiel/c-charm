#include "iset.h"
#include <algorithm>
#include <iterator>
#include <sstream>

ISet::ISet(const Set & set) {
    identifiers = set.identifiers;
    first_class_id = set.first_class_id;
    single_class = set.single_class;
    sup = set.transactions.size();
}

bool ISet::is_subsumed(const ISet& other) const {
    vector<int>::const_iterator at;
    for (at=other.identifiers.begin(); at!=other.identifiers.end(); ++at) {
        if (find(identifiers.begin(), identifiers.end(), *at)==identifiers.end()) {
            return false;       
        }
    }
    return true;
}

bool ISet::operator==(const ISet& other) {
	return sup == other.sup && equal(identifiers.begin(), identifiers.end(), other.identifiers.begin());
}

int ISet::support() const {
    return sup;
}

string ISet::print() const {
    stringstream ss;

    vector<int>::const_iterator it;
    for (it=identifiers.begin(); it!=identifiers.end(); ++it) {
        ss << *it;
        ss << " ";
    }
    return ss.str();
}

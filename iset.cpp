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
	vector<int> temporary;
	set_difference(other.identifiers.begin(), other.identifiers.end(), identifiers.begin(), identifiers.end(), back_inserter(temporary));
	return temporary.empty();
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

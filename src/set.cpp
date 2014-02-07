#include "set.h"
#include <algorithm>
#include <iterator>

Set::Set(vector<int> i, vector<int> t) {
	identifiers = i;
	sort(identifiers.begin(), identifiers.end());
	transactions = t;
	sort(transactions.begin(), transactions.end());
    first_class_id = -1;
    single_class = true;
}

Set::Set(const Set& ref) {
    identifiers = ref.identifiers;
	sort(identifiers.begin(), identifiers.end());
    transactions = ref.transactions;
	sort(transactions.begin(), transactions.end());
    first_class_id = ref.first_class_id;
    single_class = ref.single_class;
}

bool Set::is_subset_of(const Set& other) const {
    vector<int>::const_iterator at;
    for (at=transactions.begin(); at!=transactions.end(); ++at) {
        if (find(other.transactions.begin(), other.transactions.end(), *at)==other.transactions.end()) {
            return false;       
        }
    }
    return true;
}

bool Set::operator==(const Set& other) {
	return transactions.size() == other.transactions.size()
        && equal(transactions.begin(), transactions.end(), other.transactions.begin());
}

int Set::support() const {
    return transactions.size();
}

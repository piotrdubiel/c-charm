#include "set.h"
#include <algorithm>
#include <iterator>

Set::Set(vector<int> i, vector<int> t) {
	this->identifiers = i;
	sort(identifiers.begin(), identifiers.end());
	this->transactions = t;
	sort(transactions.begin(), transactions.end());
}

Set::Set(const Set& ref) {
    identifiers = ref.identifiers;
	sort(identifiers.begin(), identifiers.end());
    transactions = ref.transactions;
	sort(transactions.begin(), transactions.end());
    first_class_id = ref.first_class_id;
    single_class = ref.single_class;
}

bool Set::is_subset_of(const Set& other) {
	vector<int> temporary;
	set_difference(transactions.begin(), transactions.end(), other.transactions.begin(), other.transactions.end(), back_inserter(temporary));
	return temporary.empty();
}

bool Set::operator==(const Set& other) {
	return transactions.size() == other.transactions.size() && equal(transactions.begin(), transactions.end(), other.transactions.begin());
}

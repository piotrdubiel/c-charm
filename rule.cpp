#include "rule.h"

Rule::Rule(ISet* s, pair<int, string> c, string d) {
    set = s;
	class_attribute = c;
	decision = d;
}

void Rule::add_attribute(string name, string value) {
    attributes[name] = value;
}

bool Rule::has_superset_of(const ISet& other) const {
	return other.is_subsumed(*set);
}

#include "rule.h"

Rule::Rule(ISet* s) {
    set = s;
}

void Rule::add_attribute(string name, string value) {
    attributes.insert(pair<string, string>(name, value));
}

bool Rule::is_subset_of(const ISet& other) const {
    return set->is_subsumed(other);
}

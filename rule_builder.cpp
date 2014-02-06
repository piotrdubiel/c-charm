#include "rule_builder.h"

#include <string>
#include <algorithm>

RuleBuilder::RuleBuilder(DataSet * d): data_set(d) {}

struct identifier_length {
    bool operator() (ISet* a, ISet* b) {
        return a->identifiers.size() < b->identifiers.size();
    }
} length_compartor;

map<int, list<Rule> > RuleBuilder::build(vector<ISet*> sets) {
    sort(sets.begin(), sets.end(), length_compartor);

    map<int, list<Rule> > rules;

    vector<int> identifiers = data_set->get_identifiers(data_set->get_id(sets.front()->first_class_id).first);

    vector<ISet*>::iterator it;
    for (it=sets.begin(); it!=sets.end(); ++it) {
		if (!(*it)->single_class) continue;

        int decision = (*it)->first_class_id;
		pair<int, string> decision_mapped = data_set->get_id(decision);
		Rule rule(*it, pair<int,string>(decision_mapped.first, data_set->get_attribute(decision_mapped.first)), decision_mapped.second);


        vector<int>::iterator id;
        for (id=identifiers.begin(); id!=identifiers.end(); ++id) {
            pair<int, string> remapped = data_set->get_id(*id);
            if (find((*it)->identifiers.begin(), (*it)->identifiers.end(), *id)!=(*it)->identifiers.end()) {
				rule.add_attribute(data_set->get_attribute(remapped.first), remapped.second);
            }
			else if (rule.attributes.count(data_set->get_attribute(remapped.first))==0) {
				rule.add_attribute(data_set->get_attribute(remapped.first), "");
            }
        }

        if (rules.count(decision)>0) {
            list<Rule>::iterator tt;
			bool can_add = true;
            for (tt=rules[decision].begin(); tt!=rules[decision].end(); ++tt) {
                if (tt->has_superset_of(**it)) {
					can_add = false;
                    break;
                }
            }
			if (can_add) {
				rules[decision].push_back(rule);
			}
        }
        else {
            list<Rule> addition;
            addition.push_back(rule);
            rules[decision] = addition;
        }
    }
    return rules;
}

map<int, string> DataSet::get_attributes() const {
	return attribute_map;
}

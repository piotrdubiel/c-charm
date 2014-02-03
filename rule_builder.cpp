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

    vector<ISet*>::iterator it;
    for (it=sets.begin(); it!=sets.end(); ++it) {
        cout << "length " << (*it)->identifiers.size() <<endl;
        int decision = (*it)->first_class_id;
        Rule rule(*it);

        vector<int>::iterator id;
        for (id=(*it)->identifiers.begin(); id!=(*it)->identifiers.end(); ++id) {
            pair<int, string> remapped = data_set->remap(*id);
            rule.add_attribute(data_set->get_attribute(remapped.first), remapped.second);
        }

        if (rules.count(decision)>0) {
            list<Rule>::iterator tt;
            for (tt=rules[decision].begin(); tt!=rules[decision].end(); ++tt) {
                if (tt->is_subset_of(**it)) {
                    cout << (*it)->print() << endl;
                    cout << tt->set->print() << endl;
                    cout << "Not adding" << endl;
                    break;
                }
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

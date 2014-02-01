#include "rule_builder.h"

#include <string>

RuleBuilder::RuleBuilder(DataSet * d): data_set(d) {}

map<int, Rule> RuleBuilder::build(list<ISet*> sets) const {
    map<int, list<Rule> > rules;
    list<ISet*>::const_iterator it;
    for (it=sets.begin(); it!=set.end(); ++it) {
        rules.insert
    }

}

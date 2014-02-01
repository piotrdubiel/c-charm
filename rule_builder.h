#ifndef RULE_BUILDER_H
#define RULE_BUILDER_H

#include <list>
#include <map>
#include "rule.h"
#include "iset.h"
#include "data_set.h"

using namespace std;

class RuleBuilder {
    private:
        DataSet * data_set;
    public:
        RuleBuilder(DataSet *);
        map<int, list<Rule> > build(list<ISet*>) const;
};

#endif RULE_BUILDER_H

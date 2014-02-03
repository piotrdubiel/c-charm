#ifndef RULE_BUILDER_H
#define RULE_BUILDER_H

#include <list>
#include <vector>
#include <map>
#include "rule.h"
#include "iset.h"
#include "dataset.h"

using namespace std;

class RuleBuilder {
    private:
        DataSet * data_set;
    public:
        RuleBuilder(DataSet *);
        map<int, list<Rule> > build(vector<ISet*>);
};

#endif

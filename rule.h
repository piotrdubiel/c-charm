#ifndef RULE_H
#define RULE_H

#include <string>
#include <iostream>
#include <map>
#include "iset.h"

using namespace std;

class Rule {
    private:
        map<string,string> attributes;
        string decision;
    public:
        ISet* set;
        Rule(ISet*);
        void add_attribute(string, string);
        bool is_subset_of(const ISet&) const;

};

#endif

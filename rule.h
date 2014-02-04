#ifndef RULE_H
#define RULE_H

#include <string>
#include <iostream>
#include <map>
#include "iset.h"

using namespace std;

class Rule {
    public:
        map<string,string> attributes;
        pair<int, string> class_attribute;
		string decision;
    
        ISet* set;
        Rule(ISet*, pair<int,string>, string);
        void add_attribute(string, string);
        bool has_superset_of(const ISet&) const;

};

#endif

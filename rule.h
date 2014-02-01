#ifndef RULE_H
#define RULE_H

#include <string>
#include <iostream>
#include <map>

using namespace std;

class Rule {
    private:
        map<string,string> attributes;
    public:
        Rule();
        void add_attribute(string, string);

};

#endif

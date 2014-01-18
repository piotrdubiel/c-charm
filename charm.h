#ifndef CHARM_H
#define CHARM_H

#include <list>
#include "dataset.h"
#include "rule.h"

class Charm {
    

public:
    Charm() {
    
    }

    std::list<Rule> get_rules(const DataSet & data_set) {
        return std::list<Rule>();
    }

private:


};

#endif

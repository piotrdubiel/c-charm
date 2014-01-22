#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "dataset.h"
#include "charm.h"
#include "utils.h"
#include "set.h"

using namespace std;

int main() {
    ifstream car_file("test.data");
    ifstream car_header("test.names");
    DataSet d(car_header, car_file);
    d.print_identifiers();


    Charm charm(d, 4);

    vector<Set*> sets = charm.get_close_sets(0);
    return 0;
    vector<Set*>::iterator it;
    for (it=sets.begin(); it != sets.end(); ++it) {
        vector<int>::iterator i;
        for (i=(*it)->identifiers.begin(); i!=(*it)->identifiers.end(); ++i) {
            cout << *i << " ";
        }
        cout << "\tSingle class: " << (*it)->single_class << "\t   Class: " << (*it)->first_class_id << endl;
        delete *it;
    }

    cout << d.remap(0).second << endl;


    return 0;
}

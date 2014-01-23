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
    ifstream car_file("car.data");
    ifstream car_header("car.names");
    DataSet d(car_header, car_file);
    d.print_identifiers();


    Charm charm(d, 6);

    vector<Set*> sets = charm.get_close_sets(0);
    vector<Set*>::iterator it;
    for (it=sets.begin(); it != sets.end(); ++it) {
        vector<int>::iterator i;
        if ((*it)->single_class) {
            for (i=(*it)->identifiers.begin(); i!=(*it)->identifiers.end(); ++i) {
                cout << d.remap(*i).second << " ";
            }
            //cout << "\t\t\tSingle class: " << (*it)->single_class << "\t   Class: " << d.remap((*it)->first_class_id).second << endl;
            cout <<  "\t\t Class: " << d.remap((*it)->first_class_id).second << endl;
            //delete *it;
        }
    }

    return 0;
}

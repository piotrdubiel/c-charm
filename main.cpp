#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "dataset.h"
#include "charm.h"
#include "utils.h"

using namespace std;

int main() {
    ifstream car_file("car.test");
    ifstream car_header("car.names");
    DataSet d(car_header, car_file);
    d.print_identifiers();

    vector<int> tids = d.get_tids(vector<int>());//d->get_transactions(ids);
    vector<int> ids = d.get_identifiers(6);
    for (vector<int>::iterator it=tids.begin(); it != tids.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;

    Charm charm(d, 6);
    charm.get_close_sets(0);

    return 0;
}

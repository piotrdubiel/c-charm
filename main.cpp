#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "dataset.h"
#include "charm.h"

using namespace std;

int main() {
    ifstream car_file("car.data");
    ifstream car_header("car.names");
    DataSet d(car_header, car_file);
    d.print_identifiers();

    set<int> ids;
    ids.insert(1);
    vector<int> tids = d.get_identifiers();//d->get_transactions(ids);
    for (vector<int>::iterator it=tids.begin(); it != tids.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;

    Charm charm(d, 6);
    charm.get_close_sets(0);

    return 0;
}

#include <iostream>
#include <fstream>
#include <string>
#include "dataset.h"
#include "charm.h"

using namespace std;

int main() {
    ifstream car_file("car.data");
    ifstream car_header("car.names");
    DataSet * d = new DataSet(car_header, car_file);
    d->print_identifiers();
    d->print();
    delete d;
    return 0;
}

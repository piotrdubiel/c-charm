#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "dataset.h"
#include "charm.h"
#include "utils.h"

using namespace std;

int main() {
    ifstream car_file("test.data");
    ifstream car_header("test.names");
    DataSet d(car_header, car_file);
    d.print_identifiers();


    Charm charm(d, 4);
    charm.get_close_sets(0);

    return 0;
}

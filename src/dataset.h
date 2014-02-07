#ifndef DATA_SET_H
#define DATA_SET_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include "set.h"

using namespace std;

enum Order {
    NONE,
    ASCENDING,
    DESCENDING,
};

class DataSet {
    private:
    map<pair<int,string>,int> identifier_map;
    map<int, string> attribute_map;
    vector<vector<int> > transactions;

    void read_header(ifstream &);
    void read_data(ifstream &);
    void read_data_and_create_header(ifstream & input_file);
    void to_sorted(Order);
    public:
    DataSet(ifstream &, ifstream &, Order);
    DataSet(ifstream &, Order);
    int support(int id) const;
    vector<int> get_tids(vector<int> identifiers) const;
    vector<int> get_transaction(int id) const;
    vector<int> get_identifiers(int) const;
    void print_identifiers() const;
    void print() const;
    int last_attribute() const;

    pair<int, string> remap(int id) const;
    string get_attribute(int id);
	map<int, string> get_attributes() const;
};

#endif

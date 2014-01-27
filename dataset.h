#ifndef DATA_SET_H
#define DATA_SET_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

using namespace std;

class DataSet {
    map<pair<int,string>,int> identifier_map;
    map<int, string> attribute_map;
    vector<vector<int> > transactions;

    void read_header(ifstream &);
    void read_data(ifstream &);
    void read_data_and_create_header(ifstream & input_file);
public:
    DataSet(ifstream &, ifstream &);
    DataSet(ifstream &);
    int support(int id) const;
    vector<int> get_tids(vector<int> identifiers) const;
    vector<int> get_transaction(int id) const;
    vector<int> get_identifiers(int) const;
    void print_identifiers() const;
    void print() const;

    pair<int, string> remap(int id) const;
};

#endif

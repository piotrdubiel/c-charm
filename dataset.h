#ifndef DATA_SET_H
#define DATA_SET_H

#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <vector>
#include <map>

using namespace std;

class DataSet {
    map<pair<int,string>,int> identifier_map;
    list<vector<int> > transactions;


    void read_header(ifstream &);
    void read_data(ifstream &);
public:
    DataSet(ifstream &, ifstream &);
    int support(int id);


    void print_identifiers() const;
    void print() const;
};

#endif

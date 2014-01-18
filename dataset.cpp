#include "dataset.h"
#include <iostream>
#include <fstream>
#include <string>

#include "utils.h"

DataSet::DataSet(ifstream & header, ifstream & input_file) {
    if (!header.is_open() || !input_file.is_open()) throw "File not opened";
    cout << "Reading header ..." << endl;
    read_header(header);

    cout << "Creating dataset from file..." << endl;
    //read_data(input_file);
}

void DataSet::print_identifiers() const {
    map<pair<int,string>,int> >::const_iterator it;
    for (it=identifier_map.begin(); it != identifier_map.end(); ++it) {
        cout << it->first.first << "-" << it->first.second << " => " << at->second << endl;
    }
}

void DataSet::print() const {
    list<vector<int> >::const_iterator it;
    for (it=transactions.begin(); it != transactions.end(); ++it) {
        vector<int>::const_iterator at;
        for (at=it->begin(); at != it->end(); ++at) {
            cout << *at << " \t";
        }
        cout << endl;
    }
}

void DataSet::read_header(ifstream & header) {
    string line;
    int current_identifier = 0;
    int current_attribute = 0;

    while (getline(header,line)) {
        if (line[0] == '|' || line == "") continue;
        cout << line << endl;
        map<string,int> attribute_map;
        if (line.find(':') != std::string::npos) {
        }
        else {
            vector<string> tokens = Utils::split(line, ', ');
            vector<string>::iterator it;

            for (it=tokens.begin(); it != tokens.end(); ++it) {


                if (attribute_map.insert(pair<string,int>(*it,current_identifier)).second) {
                    current_identifier++;
                }
                attributes.push_back(identifier_map[*it]);


                pair<string, string> key;


            }
            if (identifier_map.insert(pair<string,int>(*it,current_identifier)).second) {
                current_identifier++;
            }
        }
        identifier_map.push_back(attribute_map);
        header.close();
    }
}

void DataSet::read_data(ifstream & input_file) {
    string line;
    while (getline(input_file,line)) {
        vector<string> tokens = Utils::split(line, ',');
        vector<int> attributes;
        for (int i = 0; i < tokens.size(); ++i) {
            attributes.push_back(identifier_map[i][tokens[i]]);
        }
        transactions.push_back(attributes);
    }
    input_file.close();
}

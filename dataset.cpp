#include "dataset.h"
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

#include "utils.h"

DataSet::DataSet(ifstream & header, ifstream & input_file) {
    if (!header.is_open() || !input_file.is_open()) throw "File not opened";
    cout << "Reading header ..." << endl;
    read_header(header);

    cout << "Creating dataset from file..." << endl;
    read_data(input_file);
}

void DataSet::print_identifiers() const {
    cout << "HEADER" << endl;
    map<pair<int,string>,int>::const_iterator it;
    for (it=identifier_map.begin(); it != identifier_map.end(); ++it) {
        cout << it->first.first << "-" << it->first.second << " => " << it->second << endl;
    }
}

void DataSet::print() const {
    vector<vector<int> >::const_iterator it;
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


    vector<string> lines;

    while (getline(header,line)) {
        if (line == "" || line[0] == '|') continue;
        lines.push_back(line);
    }

    vector<string>::iterator ll;
    for (ll=lines.begin(); ll != lines.end(); ++ll) {
        string line = *ll;
        vector<string> tokens;
        if (line.find(':') != std::string::npos) {
            tokens = Utils::split(line.substr(line.find_first_of(':') + 1), ' ');

            vector<string>::iterator it;
            for (it=tokens.begin(); it != tokens.end(); ++it) {
                if (*it == "") continue;
                // cut the last character
                it->erase(--it->end(), it->end());
                if (identifier_map.insert(
                            pair<pair<int,string>, int>(
                                pair<int, string>(current_attribute, Utils::trim(*it)),
                                current_identifier)
                            ).second) {
                    current_identifier++;
                }
            }
            current_attribute++;
        }
        else {
            tokens = Utils::split(line, ',');
            vector<string>::iterator it;
            for (it=tokens.begin(); it != tokens.end(); ++it) {
                if (identifier_map.insert(
                            pair<pair<int,string>, int>(
                                pair<int, string>(lines.size() - 1, Utils::trim(*it)),
                                current_identifier)
                            ).second) {
                    current_identifier++;
                }
            }
        }
    }
    header.close();
}

void DataSet::read_data(ifstream & input_file) {
    string line;
    while (getline(input_file,line)) {
        vector<string> tokens = Utils::split(line, ',');
        vector<int> attributes;
        for (int i = 0; i < tokens.size(); ++i) {
            pair<int,string> element(i, Utils::trim(tokens[i]));
            if (identifier_map.count(element) == 0) {
				attributes.push_back(-1);
			}
			else {
				attributes.push_back(identifier_map[element]);
			}
        }
        transactions.push_back(attributes);
    }
    input_file.close();
}

int DataSet::support(int id) const {
    int sup = 0;
    vector<vector<int> >::const_iterator it;
    for (it=transactions.begin(); it != transactions.end(); ++it) {
        if (find(it->begin(), it->end(), id) != it->end()) {
            sup++;
        }
    }
    return sup;
}

vector<int> DataSet::get_tids(vector<int> identifiers) const {
    vector<int> tids;
    for (int i = 0; i < transactions.size(); ++i) {
        if (identifiers.empty()) tids.push_back(i);
        else {
            vector<int>::const_iterator is;
            for (is=identifiers.begin(); is!=identifiers.end(); ++is) {
                if (find(transactions[i].begin(), transactions[i].end(), *is) != transactions[i].end()) {
                    tids.push_back(i);
                }
            }
        }
    }
    return tids;
}

vector<int> DataSet::get_identifiers(int class_id) const {
    vector<int> identifiers;
    map<pair<int,string>, int>::const_iterator it;
    for (it=identifier_map.begin(); it != identifier_map.end(); ++it) {
        if (it->first.first != class_id) {
            identifiers.push_back(it->second);
        }
    }
    return identifiers;
}

vector<int> DataSet::get_transaction(int id) const {
    return transactions[id];
}

#include "dataset.h"
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <sstream>

#include "utils.h"

DataSet::DataSet(ifstream & header, ifstream & input_file, Order order) {
    if (!header.is_open() || !input_file.is_open()) throw exception();
    read_header(header);
    read_data(input_file);

    if (order != NONE) {
        to_sorted(order);
    }
    transactions.clear();
    read_data(input_file);
    header.close();
    input_file.close();
}

DataSet::DataSet(ifstream & input_file, Order order) {
    if (!input_file.is_open()) throw exception();
    read_data_and_create_header(input_file);

    if (order != NONE) {
        to_sorted(order);
    }
    transactions.clear();
    read_data(input_file);
    input_file.close();
}

void DataSet::print_identifiers() const {
    cout << "HEADER" << endl;
    map<int,string>::const_iterator jj;
    for (jj=attribute_map.begin(); jj != attribute_map.end(); ++jj) {
        cout << jj->second << endl;
    }

    map<int, pair<int,string> >::const_iterator it;
    for (it=identifier_map.begin(); it != identifier_map.end(); ++it) {
        vector<int> ids;
        ids.push_back(it->first);
        cout << it->second.first << "-" << it->second.second << " => " << it->first << " sup: " << get_tids(ids).size() << endl;
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
                            pair<int, pair<int,string> >(
                                current_identifier,
                                pair<int, string>(current_attribute, Utils::trim(*it)))
                            ).second) {
                    current_identifier++;
                }
            }
            attribute_map.insert(pair<int, string>(current_attribute, Utils::split(line, ':')[0]));
            current_attribute++;
        }
        else {
            tokens = Utils::split(line, ',');
            vector<string>::iterator it;
            for (it=tokens.begin(); it != tokens.end(); ++it) {
                if (identifier_map.insert(
                            pair<int ,pair<int,string> >(
                                current_attribute,
                                pair<int, string>(lines.size() - 1, Utils::trim(*it)))
                            ).second) {
                    current_identifier++;
                }
            }
            attribute_map.insert(pair<int, string>(lines.size() - 1, "decision"));
        }
    }
}

void DataSet::read_data(ifstream & input_file) {
    input_file.clear();
    input_file.seekg(0);
    string line;
    while (getline(input_file,line)) {
        vector<string> tokens = Utils::split(line, ',');
        vector<int> attributes;
        for (int i = 0; i < tokens.size(); ++i) {
            pair<int,string> element(i, Utils::trim(tokens[i]));
            if (remap(element) == -1) {
                attributes.push_back(-1);
            }
            else {
                attributes.push_back(remap(element));
            }
        }
        transactions.push_back(attributes);
    }
}

void DataSet::read_data_and_create_header(ifstream & input_file) {
    string line;
    int current_id = 0;
    while (getline(input_file,line)) {
        vector<string> tokens = Utils::split(line, ',');
        vector<int> attributes;
        for (int i = 0; i < tokens.size(); ++i) {
            if (tokens[i] == "") {
                attributes.push_back(-1);
            }
            else {
                pair<int,string> element(i, Utils::trim(tokens[i]));
                if (identifier_map.insert(pair<int, pair<int, string> >(current_id, element)).second) {
                    current_id++;
                }
                attributes.push_back(remap(element));
            }
        }
        transactions.push_back(attributes);
    }
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
    map<int, pair<int,string> >::const_iterator it;
    for (it=identifier_map.begin(); it != identifier_map.end(); ++it) {
        if (it->second.first != class_id) {
            identifiers.push_back(it->first);
        }
    }
    sort(identifiers.begin(), identifiers.end());
    return identifiers;
}

vector<int> DataSet::get_transaction(int id) const {
    return transactions[id];
}


int DataSet::remap(pair<int, string> element) const {
    map<int, pair<int,string> >::const_iterator it;
    for (it=identifier_map.begin(); it!=identifier_map.end(); ++it) {
        if (it->second == element) return it->first;
    }
    return -1;
}

struct ascending_struct {
    bool operator() (pair<int, int> i, pair<int, int> j) {
        return i.second < j.second;
    }
} ascending_comparator;

struct descending_struct {
    bool operator() (pair<int, int> i, pair<int, int> j) {
        return i.second > j.second;
    }
} descending_comparator;

void DataSet::to_sorted(Order order) {
    vector<pair<int, int> > supports;

    map<int, pair<int,string> >::iterator it;
    for (it=identifier_map.begin(); it != identifier_map.end(); ++it) {
        vector<int> ids;
        ids.push_back(it->first);
        supports.push_back(pair<int, int>(it->first, get_tids(ids).size()));
    }

    if (order == ASCENDING) {
        sort(supports.begin(), supports.end(), ascending_comparator);
    }
    else {
        sort(supports.begin(), supports.end(), descending_comparator);
    }

    int new_identifier = 0;
    vector<pair<int,int> >::iterator ii;
    map<int, pair<int,string> > old_identifier_map(identifier_map);
    for (ii=supports.begin(); ii != supports.end(); ++ii) {
        cout<< ii->first << " " << ii->second << endl;
        map<int, pair<int,string> >::iterator tt;
        for (tt=old_identifier_map.begin(); tt!=old_identifier_map.end(); ++tt) {
            if (ii->first == tt->first) {
                identifier_map[new_identifier++] = tt->second;
                break;   
            }
        }
    }

}

int DataSet::last_attribute() const {
    int max = -1;
    map<int, pair<int,string> >::const_iterator it;
    for (it=identifier_map.begin(); it != identifier_map.end(); ++it) {
        if (it->second.first > max) {
            max = it->second.first;
        }
    }
    return max;
}

string DataSet::get_attribute(int id) {
    if (attribute_map.count(id)>0) {
        return attribute_map[id];
    }
    else {
		stringstream ss;
		ss << "Attribute " << id;
		return ss.str();
    }
}

pair<int, string> DataSet::get_id(int id) const {
    if (identifier_map.count(id) > 0) {
        return identifier_map.find(id)->second;
    }
    else {
        return pair<int, string>(-1, "Unknown");
    }
}

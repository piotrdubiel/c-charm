#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "dataset.h"
#include "charm.h"
#include "utils.h"
#include "set.h"

using namespace std;

void usage();

// TODO
// - dont store tid set in hashtable
// - delete tidsets after use
// - finish subsum checking
// - add ordering of identifiers

int main(int argc, char* argv[]) {
    char* data_filename;
    char* header_filename;
    Order order = NONE;
    if (argc == 3) {
        header_filename = argv[1];   
        data_filename = argv[2];   
    }
    else if (argc == 4) {
        header_filename = argv[2];
        data_filename = argv[3];

        if (argv[1] == "-a" || argv[1] == "--asc") {
            order = ASCENDING;
        }
        else if (argv[1] == "-d" || argv[1] == "--desc") {
            order = DESCENDING;
        }
        else {
            cout << "Unknown parameter: " << argv[1] << endl;
            usage();
            return 2;
        }
    }
    else {
        usage();
        return 1;
    }

    ifstream data_file(data_filename);
    ifstream header_file(header_filename);
    DataSet d(header_file, data_file);

    d.print_identifiers();
    Charm charm(d, 4);

    vector<Set*> sets = charm.get_close_sets(0);
    vector<Set*>::iterator it;
    for (it=sets.begin(); it != sets.end(); ++it) {
        vector<int>::iterator i;
        //if ((*it)->single_class) {
            for (i=(*it)->identifiers.begin(); i!=(*it)->identifiers.end(); ++i) {
                cout << d.remap(*i).second << " ";
            }
            //cout << "\t\t\tSingle class: " << (*it)->single_class << "\t   Class: " << d.remap((*it)->first_class_id).second << endl;
            cout <<  "\t\t Class: " << d.remap((*it)->first_class_id).second << " single: " << (*it)->single_class << " support: " << (*it)->support() <<  endl;
            //delete *it;
        //}
    }

    return 0;
}

void usage() {
    cout << "charm is a tool for finding rules in dataset" << endl;
    cout << "Usage: charm [options] HEADER DATASET" << endl;
    cout << "Options" << endl;
    cout << "\t-a, --asc\tOrder by ascending support" << endl; 
    cout << "\t-d, --desc\tOrder by descending support" << endl; 
}

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stdlib.h>
#include <string.h>
#include "dataset.h"
#include "charm.h"
#include "utils.h"
#include "set.h"
#include "writer.h"

using namespace std;

void usage();

// TODO
// - delete tidsets after use
// - add ordering of identifiers

int main(int argc, char* argv[]) {
    char* data_filename = NULL;
    char* header_filename = NULL;
    char* output_filename = NULL;
    Order order = NONE;
    OutputType output_type = TEXT;
    int min_sup = 0;
    int class_attribute = -1;
    
    if (argc < 3 || argc > 12) {
        usage();
        return 2;
    }
    
    for (int i = 1; i <= argc - 3; ++i) {
        if (strcmp(argv[i], "-h")==0 || strcmp(argv[i], "--header")==0) {
            header_filename = argv[++i];
        }
        else if (strcmp(argv[i], "-a")==0 || strcmp(argv[i], "--asc")==0) {
            if (order == NONE) {
                order = ASCENDING;
            }
            else {
                cerr << "Two ordering defined" << argv[i] << endl;
                usage();
                return 2;
            }
        }
        else if (strcmp(argv[i], "-d")==0 || strcmp(argv[i], "--desc")==0) {
            if (order == NONE) {
                order = DESCENDING;
            }
            else {
                cerr << "Two ordering defined." << endl;
                usage();
                return 2;
            }
        }
        else if (strcmp(argv[i], "-s")==0 || strcmp(argv[i], "--support")==0) {
            min_sup = atoi(argv[++i]);
        }
        else if (strcmp(argv[i], "-f")==0 || strcmp(argv[i], "--format")==0) {
            if (strcmp(argv[i+1], "csv")==0) {
                output_type = CSV;
            }
            else if (strcmp(argv[i+1], "text")==0) {
                output_type = CSV;
            }
            else {
                cerr << "Unknown formatting: " << argv[i+1] << endl;
            }
            i++;
        }
        else if (strcmp(argv[i], "-c")==0 || strcmp(argv[i], "--class")==0) {
            class_attribute = atoi(argv[++i]);
            if (class_attribute == 0 && strcmp(argv[i], "0")!=0) {
                cerr << "Wrong class identifier: " << argv[i] << endl;
            }
        }
        else {
            cerr << "Unknown parameter: " << argv[i] << endl;
            usage();
            return 1;
        }
    }
    
    data_filename = argv[argc-2];   
    output_filename = argv[argc-1];   

    if (!Utils::exists(data_filename)) {
        cerr << "Data file doesn't exist: " << data_filename << endl;
        return 4;
    }

    if (header_filename && !Utils::exists(header_filename)) {
        cerr << "Header file doesn't exist: " << header_filename << endl;
        return 4;
    }

    DataSet* data;
    if (header_filename) {
        ifstream header_file(header_filename);
        ifstream data_file(data_filename);
        data = new DataSet(header_file, data_file, order);
    }
    else {
        ifstream data_file(data_filename);
        data = new DataSet(data_file, order);
    }



    data->print_identifiers();
    return 9;
    Charm charm(data, class_attribute, min_sup);


    vector<ISet*> sets = charm.get_close_sets(0);
    vector<ISet*>::iterator it;
    for (it=sets.begin(); it != sets.end(); ++it) {
        vector<int>::iterator i;
        //if ((*it)->single_class) {
        for (i=(*it)->identifiers.begin(); i!=(*it)->identifiers.end(); ++i) {
            cout << data->remap(*i).second << " ";
        }
        //cout << "\t\t\tSingle class: " << (*it)->single_class << "\t   Class: " << data->remap((*it)->first_class_id).second << endl;
        cout <<  "\t\t Class: " << data->remap((*it)->first_class_id).second << " single: " << (*it)->single_class << " support: " << (*it)->support() <<  endl;
        //delete *it;
        //}
    }

    return 0;
}

void usage() {
    cout << "charm is a tool for finding rules in dataset" << endl;
    cout << "Usage: charm [options] DATASET OUTPUT" << endl;
    cout << "Options" << endl;
    cout << "\t-a, --asc\t\tOrder by ascending support" << endl; 
    cout << "\t-d, --desc\t\tOrder by descending support" << endl; 
    cout << "\t-f, --format FORMAT\tFormat of output [csv,text]. Default - 'text'" << endl; 
    cout << "\t-h, --header FILE\tHeader file" << endl; 
    cout << "\t-s, --support SUPPORT\tMinimum support. Default - 0." << endl; 
    cout << "\t-c, --class COLUMN\tDecison attribute index [0..number of attributes - 1]. Default - last attribute in data set." << endl; 

}

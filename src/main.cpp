#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "dataset.h"
#include "charm.h"
#include "utils.h"
#include "set.h"
#include "writer.h"
#include "text_writer.h"
#include "csv_writer.h"
#include "rule_builder.h"

using namespace std;

void usage();

int main(int argc, char* argv[]) {
    char* data_filename = NULL;
    char* header_filename = NULL;
    char* output_filename = NULL;
    Order order = NONE;
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
            cout << "Minimum support: " << min_sup << endl;

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

    clock_t start = clock();
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

    Charm * charm;
    if (class_attribute != -1) {
        charm = new Charm(data, class_attribute, min_sup);
    }
    else {
        charm = new Charm(data, min_sup);
    }

    vector<ISet*> sets = charm->get_close_sets();

    RuleBuilder builder(data);

    map<int, list<Rule> > rules = builder.build(sets);
    
    ofstream text_output(string(output_filename).append(".txt").c_str());
	TextWriter::write(text_output, rules);
    text_output.close();
    ofstream csv_output(string(output_filename).append(".csv").c_str());
	CsvWriter::write(csv_output, rules);
    csv_output.close();

    delete charm;
    cout << ((float) (clock() - start)) / CLOCKS_PER_SEC << "s" << endl;

    return 0;
}

void usage() {
    cout << "charm is a tool for finding rules in dataset" << endl;
    cout << "Usage: charm [options] DATASET OUTPUT" << endl;
    cout << "Options" << endl;
    cout << "\t-a, --asc\t\tOrder by ascending support" << endl; 
    cout << "\t-d, --desc\t\tOrder by descending support" << endl; 
    cout << "\t-h, --header FILE\tHeader file" << endl; 
    cout << "\t-s, --support SUPPORT\tMinimum support. Default - 0." << endl; 
    cout << "\t-c, --class COLUMN\tDecison attribute index [0..number of attributes - 1]. Default - last attribute in data set." << endl; 

}

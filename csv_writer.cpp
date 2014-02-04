#include "csv_writer.h"

void CsvWriter::write(ostream & output, map<int, list<Rule> > rules, DataSet* data) {
    // write header
    int class_id = rules.begin()->second.front().class_attribute.first;
    //vector<int> identifiers = data

	map<int, list<Rule> >::iterator im;
	for (im=rules.begin(); im!=rules.end(); ++im) {
		list<Rule>::iterator ir;
		for (ir=im->second.begin(); ir!=im->second.end(); ++ir) {
             


			map<string, string>::iterator ia;
			for (ia=ir->attributes.begin(); ia!=ir->attributes.end(); ++ia) {
				output << ia->first << "(" << ia->second << ")";
				if (ir->attributes.size() > 1 && ia!=--ir->attributes.end()) {
					output << ", ";
				}
			}
			output << endl;
		}
		output << endl;
	}
    
    output.flush();
}

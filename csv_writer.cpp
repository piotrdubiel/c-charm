#include "csv_writer.h"

void CsvWriter::write(ostream & output, map<int, list<Rule> > rules, DataSet* data) {
    // write header
	map<string, string>::iterator at;
	for (at=rules.begin()->second.front().attributes.begin(); at!=rules.begin()->second.front().attributes.end(); ++at) {
		output << at->first << ";";		
	}
	output << rules.begin()->second.front().class_attribute.second << endl;

	map<int, list<Rule> >::iterator im;
	for (im=rules.begin(); im!=rules.end(); ++im) {
		list<Rule>::iterator ir;
		for (ir=im->second.begin(); ir!=im->second.end(); ++ir) {
            map<string, string>::iterator ia;
			for (ia=ir->attributes.begin(); ia!=ir->attributes.end(); ++ia) {
				if (ia->second!="") {
					output << ia->second;
				}
				output << ";";
			}
			output << ir->decision;
			output << endl;
		}
	}
    
    output.flush();
}

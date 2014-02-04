#include "text_writer.h"

void TextWriter::write(ofstream & output, map<int, list<Rule> > rules) {
	map<int, list<Rule> >::iterator im;
	for (im=rules.begin(); im!=rules.end(); ++im) {
		output << "====================" << endl;
		output << im->second.front().class_attribute << ": ";
		output << im->second.front().decision << endl;
		output << "--------------------" << endl;

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
    output.close();
}

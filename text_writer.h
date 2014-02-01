#ifndef TEXT_WRITER_H
#define TEXT_WRITER_H

#include "writer.h"

class TextWriter : Writer {
    static void write(ofstream &, vector<ISet*>);
};

#endif

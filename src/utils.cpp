#include "utils.h"

#include <sstream>
#include <algorithm>
#include <functional>
#include <locale>
#include <set>

vector<string> Utils::split(const string & text, char delim) {
    vector<string> tokens;
    stringstream ss(text);
    string item;
    while (getline(ss, item, delim)) {
        tokens.push_back(item);
    }
    return tokens;
}

string& Utils::ltrim(string & text) {
    text.erase(text.begin(), find_if(text.begin(), text.end(), not1(ptr_fun<int, int>(isspace))));
    return text;
}

string& Utils::rtrim(string & text) {
    text.erase(find_if(text.rbegin(), text.rend(), not1(ptr_fun<int, int>(isspace))).base(), text.end());
    return text;
}

string& Utils::trim(string & text) {
    return ltrim(rtrim(text));
}

bool Utils::exists(const string & filename) {
    if (FILE *file = fopen(filename.c_str(), "r")) {
        fclose(file);
        return true;
    } else {
        return false;
    } 
}

#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include <string>
#include <set>

using namespace std;

class Utils {
public:
    static vector<std::string> split(const string &, char);
    static string& rtrim(string &);
    static string& ltrim(string &);
    static string& trim(string &);
    static bool exists(const string&);
};

#endif

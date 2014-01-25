#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include <string>
#include <set>

using namespace std;
enum Order {
    NONE,
    ASCENDING,
    DESCENDING,
};

class Utils {
public:
    static vector<std::string> split(const string &, char);
    static string& rtrim(string &);
    static string& ltrim(string &);
    static string& trim(string &);
    template<class T> static vector<T> unionv(vector<T>, vector<T>);
};

#endif

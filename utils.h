#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include <string>

class Utils {
public:
    static std::vector<std::string> split(const std::string &, char);
    static std::string& rtrim(std::string &);
    static std::string& ltrim(std::string &);
    static std::string& trim(std::string &);
};

#endif

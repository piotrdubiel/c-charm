#include "utils.h"

#include <sstream>
#include <algorithm>
#include <functional>
#include <locale>

std::vector<std::string> Utils::split(const std::string & text, char delim) {
    std::vector<std::string> tokens;
    std::stringstream ss(text);
    std::string item;
    while (std::getline(ss, item, delim)) {
        tokens.push_back(item);
    }
    return tokens;
}

std::string& Utils::ltrim(std::string & text) {
    text.erase(text.begin(), std::find_if(text.begin(), text.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
    return text;
}

std::string& Utils::rtrim(std::string & text) {
    text.erase(std::find_if(text.rbegin(), text.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), text.end());
    return text;
}

std::string& Utils::trim(std::string & text) {
    return ltrim(rtrim(text));
}

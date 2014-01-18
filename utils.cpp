#include "utils.h"

#include <sstream>

std::vector<std::string> Utils::split(const std::string & text, char delim) {
    std::vector<std::string> tokens;
    std::stringstream ss(text);
    std::string item;
    while (std::getline(ss, item, delim)) {
        tokens.push_back(item);
    }
    return tokens;
}

#ifndef DEF_UTILS
#define DEF_UTILS

#include <sstream>

static int toInt(std::string str){
    std::stringstream ss(str);
    int n;
    ss >> n;
    return n;
}

static std::string toString(int n){
    std::stringstream ss;
    ss << n;
    return ss.str();
}

static bool toBool(std::string str){
    std::stringstream ss(str);
    bool n;
    ss >> n;
    return n;
}

static std::string trim(const std::string& str, const std::string& whitespace = " \t"){
    const auto strBegin = str.find_first_not_of(whitespace);
    if (strBegin == std::string::npos)
        return ""; // no content

    const auto strEnd = str.find_last_not_of(whitespace);
    const auto strRange = strEnd - strBegin + 1;

    return str.substr(strBegin, strRange);
}

#endif

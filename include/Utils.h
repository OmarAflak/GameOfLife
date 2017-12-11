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

#endif

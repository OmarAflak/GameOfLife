#ifndef DEF_UTILS
#define DEF_UTILS

#include <sstream>

static int toInt(std::string str){
    std::stringstream ss(str);
    int n;
    ss >> n;
    return n;
}

static bool toBool(std::string str){
    std::stringstream ss(str);
    bool n;
    ss >> n;
    return n;
}

#endif

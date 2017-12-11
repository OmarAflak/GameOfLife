#ifndef DEF_UTILS
#define DEF_UTILS

#include <iostream>
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

static std::string askFilename(std::string message){
    std::stringstream ss;
    std::string input;
    std::cout << message;
    getline(std::cin, input);

    if(input==""){
        ss << time(0);
    } else{
        ss << input;
    }
    return ss.str();
}

#endif

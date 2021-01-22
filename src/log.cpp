#include <log.h>

#include <iostream>
#include <string>

#define STD_LOG_MSG "[Log] "

using namespace DSMCpp;

void Log::print(std::string msg) {
    std::cout << STD_LOG_MSG << msg << std::endl;
}
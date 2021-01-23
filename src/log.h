#pragma once

#include <string>
#include <iostream>

#define STD_LOG_MSG "[Log] "

namespace DSMCpp {
    namespace Log {

        // Needs to be here due to the template T
        template <typename T> inline void print(T msg) {
            std::cout << STD_LOG_MSG << msg << std::endl;
        }           
    
    };
};
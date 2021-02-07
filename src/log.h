#pragma once

#include <string>
#include <iostream>

#define STD_LOG_MSG "[Log] "
#define STD_ERR_MSG "[Error] "

namespace DSMCpp {
    namespace Log {

        // Needs to be here due to the template T
        template <typename T> inline void print(T msg) {
            std::cout << STD_LOG_MSG << msg << std::endl;
        }

        template <typename T> inline void error(T msg) {
            std::cout << STD_ERR_MSG << msg << std::endl;
        }           
    
    };
};
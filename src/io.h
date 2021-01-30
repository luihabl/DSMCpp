#pragma once 

#include <nlohmann/json.hpp>
#include <string>
#include <log.h>
#include <initializer_list>

namespace DSMCpp {

    using json = nlohmann::json;
    class ConfigFile {
        
        public: 
            ConfigFile() = default;
            ConfigFile(std::string path);

            template <typename T>
            inline T get(std::initializer_list<std::string> key_list) {
                json j = file;
                for (std::string key : key_list) j = j[key];
                return j.get<T>();
            }
            
        private:
            json file;
            void load_file(std::string path);
    };
}






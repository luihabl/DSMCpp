#pragma once 

#include <nlohmann/json.hpp>
#include <string>
#include <log.h>
#include <initializer_list>
#include <matrix.h>

namespace DSMCpp {

    using json = nlohmann::json;
    class ConfigFile {
        
        public: 
            ConfigFile() = default;
            ConfigFile(std::string default_path, int argc, char *argv[]);
            template <typename T> T get(std::initializer_list<std::string> key_list);
        
        private:
            json file;
            void load_file(std::string path);
    };

    namespace Output {
        template <typename T> void save_to_csv(std::string path, TMatrix<T> && m, int nrows=-1, int ncols=-1); 
        template <typename T> void save_to_csv(std::string path, TMatrix<T> & m, int nrows=-1, int ncols=-1); 
        template <typename T> void save_to_npy(std::string path, TMatrix<T> && m);
        template <typename T> void save_to_npy(std::string path, TMatrix<T> & m);
    }
}






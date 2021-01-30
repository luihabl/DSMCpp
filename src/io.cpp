#include <io.h>
#include <nlohmann/json.hpp>
#include <string>
#include<fstream>

using namespace DSMCpp;

ConfigFile::ConfigFile(std::string path) {
    load_file(path);
}

void ConfigFile::load_file(std::string path) {
    std::ifstream f(path);
    f >> file;
}


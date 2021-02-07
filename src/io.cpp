#include <io.h>
#include <log.h>
#include <matrix.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <initializer_list>
#include <vector>

#include <iostream>

#include <nlohmann/json.hpp>
#include <npy.hpp>

using namespace DSMCpp;

// ---- ConfigFile

ConfigFile::ConfigFile(std::string default_path, int argc, char *argv[]) {

    std::string path = default_path;
    if (argc > 1) path = argv[1];

    try {
        load_file(path);
    } catch (const std::exception& e) {
        Log::error("Error when loading config file: " + path);
        exit(1);
    }
    Log::error("Config file loaded: " + path);   
}

void ConfigFile::load_file(std::string path) {
    std::ifstream f(path);
    f >> file;
}

template <typename T> 
T ConfigFile::get(std::initializer_list<std::string> key_list) {
        json j = file;
        for (std::string key : key_list) j = j[key];
        return j.get<T>();
}
template int ConfigFile::get<int>(std::initializer_list<std::string> key_list);
template double ConfigFile::get<double>(std::initializer_list<std::string> key_list);
template std::string ConfigFile::get<std::string>(std::initializer_list<std::string> key_list);


// ---- Output

template <class T>
void Output::save_to_csv(std::string path,  TMatrix<T> & m, int nrows, int ncols) {

    nrows = nrows < 0 ? (int) m.n1 : nrows;
    ncols = ncols < 0 ? (int) m.n2 : ncols;

    std::ofstream file(path);
    
    for (int i = 0; i < nrows; i++) {  
        for (int j = 0; j < ncols; j++) {
            std::ostringstream stream_obj;
            stream_obj << std::setprecision(16);
            stream_obj << m.m[i * m.n2 + j];
            file << stream_obj.str();
            if (j != ncols - 1) file << ",";
        }
        file << endl;
    }
    
    file.close();
    Log::print("Data saved to " + path);
}
template void Output::save_to_csv(std::string path,  TMatrix<int> & m, int nrows, int ncols);
template void Output::save_to_csv(std::string path,  TMatrix<double> & m, int nrows, int ncols);
template void Output::save_to_csv(std::string path,  TMatrix<std::string> & m, int nrows, int ncols);

template <class T>
void Output::save_to_csv(std::string path,  TMatrix<T> && m, int nrows, int ncols) {
    nrows = nrows < 0 ? (int) m.n1 : nrows;
    ncols = ncols < 0 ? (int) m.n2 : ncols;

    std::ofstream file(path);
    
    for (int i = 0; i < nrows; i++) {  
        for (int j = 0; j < ncols; j++) {
            std::ostringstream stream_obj;
            stream_obj << std::setprecision(16);
            stream_obj << m.m[i * m.n2 + j];
            file << stream_obj.str();
            if (j != ncols - 1) file << ",";
        }
        file << endl;
    }
    
    file.close();
    Log::print("Data saved to " + path);
}
template void Output::save_to_csv(std::string path,  TMatrix<int> && m, int nrows, int ncols);
template void Output::save_to_csv(std::string path,  TMatrix<double> && m, int nrows, int ncols);
template void Output::save_to_csv(std::string path,  TMatrix<std::string> && m, int nrows, int ncols);

template <typename T> 
void Output::save_to_npy(std::string path, TMatrix<T> && m) {
    std::vector<T> data (m.m, m.m + (m.n1 * m.n2 * m.n3 ));
    const long unsigned leshape [] = {m.n1, m.n2, m.n3};
    int ndim = 3 - (m.n3 < 2) - (m.n2 < 2) - (m.n1 < 2);
    npy::SaveArrayAsNumpy(path, false, ndim, leshape, data);
    Log::print("Data saved to " + path);
}
template void Output::save_to_npy(std::string path, TMatrix<int> && m);
template void Output::save_to_npy(std::string path, TMatrix<double> && m);

template <typename T> 
void Output::save_to_npy(std::string path, TMatrix<T> & m) {
    std::vector<T> data (m.m, m.m + (m.n1 * m.n2 * m.n3 ));
    const long unsigned leshape [] = {m.n1, m.n2, m.n3};
    npy::SaveArrayAsNumpy(path, false, 2, leshape, data);
    Log::print("Data saved to " + path);
}
template void Output::save_to_npy(std::string path, TMatrix<int> & m);
template void Output::save_to_npy(std::string path, TMatrix<double> & m);
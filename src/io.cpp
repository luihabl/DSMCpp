#include <io.h>
#include <nlohmann/json.hpp>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <matrix.h>
#include <initializer_list>
#include <log.h>

using namespace DSMCpp;

// ---- ConfigFile

ConfigFile::ConfigFile(std::string path) {
    load_file(path);
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
void Output::save_to_csv(std::string path,  TMatrix<T> * m, int nrows, int ncols) {

    nrows = nrows < 0 ? (int) m->n1 : nrows;
    ncols = ncols < 0 ? (int) m->n2 : ncols;

    std::ofstream file(path);
    
    for (int i = 0; i < nrows; i++) {  
        for (int j = 0; j < ncols; j++) {
            std::ostringstream stream_obj;
            stream_obj << std::setprecision(16);
            stream_obj << m->m[i * m->n2 + j];
            file << stream_obj.str();
            if (j != ncols - 1) file << ",";
        }
        file << endl;
    }
    
    file.close();
    Log::print("Data saved to " + path);
}
template void Output::save_to_csv(std::string path,  TMatrix<int> * m, int nrows, int ncols);
template void Output::save_to_csv(std::string path,  TMatrix<double> * m, int nrows, int ncols);
template void Output::save_to_csv(std::string path,  TMatrix<std::string> * m, int nrows, int ncols);
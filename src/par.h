#pragma once 

#include <io.h>

#define PAR_LOAD_ALL \
    PAR_LOAD(lx, double, "geometry", "lx") \
    PAR_LOAD(ly, double, "geometry", "ly") \
    \
    PAR_LOAD(nx, int, "geometry", "nx") \
    PAR_LOAD(ny, int, "geometry", "ny") \
    \
    PAR_CALC(dx, double, lx / ((double)nx - 1)) \
    PAR_CALC(dy, double, lx / ((double)ny - 1)) \
    \
    PAR_LOAD(dt, double, "time", "dt") \
    PAR_LOAD(n_steps, int, "time", "n_steps") \
    \
    PAR_LOAD(mass, double, "species", "mass") \
    PAR_LOAD(sigma, double, "species", "sigma") \
    PAR_LOAD(np_add, int, "initial_conditions", "np_add") \
    PAR_LOAD(temperature, double, "initial_conditions", "temperature") \
    PAR_LOAD(np_max, int, "sim_parameters", "np_max") \
    PAR_LOAD(pw, double, "sim_parameters", "pw") 

// TODO: Set parameters from a config file
namespace DSMCpp {
    struct Parameters {

        #define PAR_LOAD(name, type, ...) type name;
        #define PAR_CALC(name, type, ...) type name;
        PAR_LOAD_ALL
        #undef PAR_LOAD
        #undef PAR_CALC

        Parameters(ConfigFile * config) {
            #define PAR_LOAD(name, type, ...) name = config->get<type>({__VA_ARGS__});
            #define PAR_CALC(name, type, val) name = val;
            PAR_LOAD_ALL
            #undef PAR_LOAD
            #undef PAR_CALC
        };
    };

    class ParametricObj {
        public:
            ParametricObj() = default;
            ParametricObj(Parameters * _par) {par = _par;}
        protected:
            Parameters * par;
    };
}
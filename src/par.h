#pragma once 


#define PAR_LOAD_ALL \
    PAR_LOAD(lx, double, 0.1) \
    PAR_LOAD(ly, double, 0.1) \
    \
    PAR_LOAD(nx, int, 10) \
    PAR_LOAD(ny, int, 10) \
    \
    PAR_LOAD(dx, double, lx / ((double)nx - 1)) \
    PAR_LOAD(dy, double, lx / ((double)ny - 1)) \
    \
    PAR_LOAD(dt, double, 1e-7) \
    PAR_LOAD(n_steps, int, 100) \
    \
    PAR_LOAD(mass, double, 2.1801714e-25) \
    PAR_LOAD(sigma, double, 2 * 2.16e-10) \
    PAR_LOAD(np_add, int, 1e3) \
    PAR_LOAD(np_max, int, 1e5) \
    PAR_LOAD(temperature, double, 300) \
    PAR_LOAD(pw, double, 1e8)



// TODO: Set parameters from a config file
namespace DSMCpp {
    struct Parameters {

        #define PAR_LOAD(name, type, val) type name;
        PAR_LOAD_ALL
        #undef PAR_LOAD

        Parameters() {
            #define PAR_LOAD(name, type, val) name = val;
            PAR_LOAD_ALL
            #undef PAR_LOAD
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
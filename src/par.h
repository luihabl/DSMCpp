#pragma once 


// TODO: Set parameters from a config file
namespace DSMCpp {
    struct Parameters {

        Parameters() = default;

        // Geometry
        double lx = 0.1;
        double ly = 0.1;
        int nx = 10;
        int ny = 10;
        double dx = lx / ((double)nx - 1);
        double dy = ly / ((double)ny - 1);
        
        //Time
        double dt = 1e-7;
        int n_steps = 1e5;

        //Species
        double mass = 2.1801714e-25;
        double sigma = 2 * 2.16e-10;
        int np_add = 1e3;
        int np_max = 1e5;
        double temperature = 300;
        double pw = 1e5;
    };

    class ParametricObj {
        public:
            ParametricObj() = default;
            ParametricObj(Parameters * _par) {par = _par;}
        protected:
            Parameters * par;
    };
}
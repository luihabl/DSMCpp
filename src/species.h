#pragma once

#include <matrix.h>
#include <par.h>

namespace DSMCpp {
    class Species {

        public:

            Species(Parameters * _par);

            void add_n_uniform_uniform(int n, double vmin, double vmax);
            void add_n_uniform_maxwellian(int n, double temperature);

            int np; //number of active particles
            double mass;
            DoubleMat x, y, z;
            DoubleMat vx, vy, vz;

        private:
            Parameters * par;
    };
}
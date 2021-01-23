#pragma once

#include <matrix.h>

namespace DSMCpp {
    class Species {

        public:

            Species(double _mass, int _np_max);
            void add_n_uniform_uniform(int n, double vmin, double vmax);
            void add_n_uniform_maxwellian(int n, double temperature);

            int np; //number of active particles
            double mass;
            DoubleMat x, y, z;
            DoubleMat vx, vy, vz;
    };
}
#pragma once

#include <matrix.h>
#include <par.h>
#include <llist.h>
#include <unordered_map>

namespace DSMCpp {
    class Species : ParametricObj {

        public:

            Species() = default;
            Species(Parameters * _par);

            void move();
            void add_n_uniform_uniform(int n, double vmin, double vmax);
            void add_n_uniform_maxwellian(int n, double temperature);
            DoubleMat get_state_vector();
            
            int np; //number of active particles
            double mass;
            double pw; //macroparticle weight
            
            DoubleMat x, y, z;
            DoubleMat vx, vy, vz;
            std::unordered_map<int, LinkedList<int>> cmap;
    };
}
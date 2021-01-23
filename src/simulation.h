#pragma once 

#include <par.h>

namespace DSMCpp {
    class Simulation {

        public:
            Simulation(Parameters * _par);

        private:
            Parameters * par;

    };
}
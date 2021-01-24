#pragma once 

#include <par.h>
#include <species.h>
#include <bound.h>

namespace DSMCpp {
    class Simulation {

        public:
            Simulation(Parameters * _par);
            void run();
            void setup();
            void iterate();

        private:
            Parameters * par;
            Species s;
            Boundaries bound;

            int step;

    };
}
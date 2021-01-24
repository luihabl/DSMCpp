#pragma once 

#include <par.h>
#include <species.h>

namespace DSMCpp {
    class Simulation {

        public:
            Simulation(Parameters * _par);
            void run();
            void setup();
            void iterate();

            Species s;

        private:
            Parameters * par;

            int step;

    };
}
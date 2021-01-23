#pragma once 

#include <par.h>

namespace DSMCpp {
    class Simulation {

        public:
            Simulation(Parameters * _par);
            void run();
            void setup();

        private:
            Parameters * par;

            int step;

    };
}
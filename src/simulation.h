#pragma once 

#include <par.h>
#include <species.h>
#include <bound.h>
#include <mesh.h> 
#include <iostream>

namespace DSMCpp {
    class Simulation : public ParametricObj {

        public:
            using ParametricObj::ParametricObj;

            void run();
            void setup();
            void iterate();

        private:
            Species s;
            Mesh mesh;
            Boundaries bound;
            int step;
    };
}
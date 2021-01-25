#pragma once 

#include <par.h>
#include <species.h>
#include <bound.h>
#include <mesh.h> 
#include <coll.h>

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
            BoundaryHandler bound;
            CollisionHandler coll;
            int step;
    };
}
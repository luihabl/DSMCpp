#pragma once

#include <par.h>
#include <species.h>

// the Boundaries class will hold all the boundary geometry in the future
namespace DSMCpp {
    class BoundaryHandler : public ParametricObj{
        public:
            using ParametricObj::ParametricObj;
            void collisions(Species * s);
            void collisions_outer_walls(Species * s);
            void specular_reflection(Species * s, int index, int nbound, double lbound);
    };
}
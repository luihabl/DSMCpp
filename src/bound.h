#pragma once

#include <par.h>
#include <species.h>

// the Boundaries class will hold all the boundary geometry in the future
namespace DSMCpp {
    class Boundaries {
        public:
            Boundaries() = default;
            Boundaries(Parameters * _par) {par = _par;}
            void collisions(Species * s);
        
        private:
            Parameters * par;
    };
}
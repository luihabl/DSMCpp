#pragma once

#include <par.h>
#include <species.h>
#include <unordered_map>

namespace DSMCpp {

    class CollisionHandler : public ParametricObj {

        public:
            using ParametricObj::ParametricObj;
            void update_map(Species * s);  
    };
}
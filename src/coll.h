#pragma once

#include <par.h>
#include <species.h>
#include <unordered_map>

namespace DSMCpp {

    class CollisionHandler : public ParametricObj {

        public:
            CollisionHandler()=default;
            CollisionHandler(Parameters * _par);
            void update_map(Species * s); 
            void collide(Species * s);
        
        private:
            void ntc_collisions(Species * s);
            void isotropic_elastic_scattering(Species * s, int p1_index, int p2_index, double vr);

            double sigma_vr_max;
    };
}
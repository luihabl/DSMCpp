#pragma once

#include <par.h>
#include <species.h>
#include <unordered_map>
#include <vector>

namespace DSMCpp {

    class CollisionHandler : public ParametricObj {

        public:
            CollisionHandler()=default;
            CollisionHandler(Parameters * _par);
            void update_map(Species * s); 
            void collide(Species * s);
        
        private:
            void ntc_collisions(Species * s);
            void isotropic_elastic_scattering(Species * s, const int & p1_index, const int & p2_index, const double & vr, 
                const double & v1x, const double & v1y, const double & v1z,
                const double & v2x, const double & v2y, const double & v2z);
            std::unordered_map<int, std::vector<int>> cmap;
            double sigma_vr_max;
    };
}
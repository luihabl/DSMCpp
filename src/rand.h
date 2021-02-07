#pragma once
#include <random>

using namespace std;

namespace DSMCpp {
    namespace Random {

        namespace {
            static random_device r;
            static mt19937 gen(r());

            static uniform_real_distribution<float> uniform(0.0, 1.0);
            static normal_distribution<float> normal(0.0, 1.0);
        }

        inline float rand(){
            return uniform(gen);
        }

        inline int rand_int(int v0, int v1) {
            return ((float)(v1 - v0) * uniform(gen) + v0);
        }

        inline int rand_int_zero(float vmax) {
            return vmax * uniform(gen);
        }

        inline float rand(float v0, float v1){
            return (v1 - v0) * uniform(gen) + v0; 
        }

        inline float randn(){
            return normal(gen);
        }

        inline float randn(float mu, float sigma){
            return sigma * normal(gen) + mu; 
        }

    }
}
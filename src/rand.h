#pragma once
#include <random>
namespace mt {
    #include <mersenne-twister.h>
}

using namespace std;

namespace DSMCpp {
    namespace RandomCpp {

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

    namespace Random {
        inline void init(uint32_t s) {
            mt::seed(s);
        }
        
        inline double rand() {
            return (double)mt::rand_u32() / (double)UINT32_MAX;
        }

        inline double rand(double v0, double v1){
            return (v1 - v0) * ((double)mt::rand_u32() / (double)UINT32_MAX) + v0; 
        }

        inline int rand_int_zero(int vmax) {
            return mt::rand_u32() % (vmax + 1);
        }
        
    }



}
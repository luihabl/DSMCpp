#pragma once
#include <random>

using namespace std;

namespace DSMCpp {
    namespace Random {
        float rand();
        float rand(float v0, float v1);
        float randn();
        float randn(float mu, float sigma);
        int rand_int(float v0, float v1);
    }
}
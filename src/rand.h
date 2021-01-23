#pragma once
#include <random>

using namespace std;

namespace DSMCpp {
    namespace Random {
        double rand();
        double randn();
        double randn(double mu, double sigma);
    }
}
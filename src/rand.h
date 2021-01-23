#pragma once
#include <random>

using namespace std;

namespace DSMCpp {
    namespace Random {
        double rand();
        double rand(double v0, double v1);
        double randn();
        double randn(double mu, double sigma);
    }
}
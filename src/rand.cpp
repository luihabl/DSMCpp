#include <rand.h>
#include <random>

using namespace std;
using namespace DSMCpp;

namespace {
    random_device r;
    seed_seq seed{ r(), r(), r(),  r() };
    mt19937 gen{ seed };

    uniform_real_distribution<float> uniform(0.0, 1.0);
    normal_distribution<float> normal(0.0, 1.0);
}

float Random::rand(){
    return uniform(gen);
}

int Random::rand_int(float v0, float v1) {
    return floor((v1 - v0) * uniform(gen) + v0);
}

float Random::rand(float v0, float v1){
    return (v1 - v0) * uniform(gen) + v0; 
}

float Random::randn(){
    return normal(gen);
}

float Random::randn(float mu, float sigma){
    return sigma * normal(gen) + mu; 
}
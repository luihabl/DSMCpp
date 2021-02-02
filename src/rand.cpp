#include <rand.h>
#include <random>

using namespace std;
using namespace DSMCpp;

namespace {
    random_device r;
    seed_seq seed{ r(), r(), r(),  r() };
    mt19937 gen{ seed };

    uniform_real_distribution<float> uniform(0.0, 1.0);
    normal_distribution<double> normal(0.0, 1.0);
    uniform_int_distribution<unsigned short> uniform_int(0, 100000);
}

double Random::rand(){
    return uniform(gen);
}

int Random::rand_int(float v0, float v1) {
    // return uniform_int(gen);
    return floor((v1 - v0) * uniform(gen) + v0);
}

double Random::rand(double v0, double v1){
    return (v1 - v0) * uniform(gen) + v0; 
}

double Random::randn(){
    return normal(gen);
}

double Random::randn(double mu, double sigma){
    return sigma * normal(gen) + mu; 
}
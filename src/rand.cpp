#include <rand.h>
#include <random>

using namespace std;
using namespace DSMCpp;

namespace {
    random_device r;
    seed_seq seed{ r(), r(), r(),  r() };
    mt19937 gen{ seed };

    uniform_real_distribution<double> uniform(0.0, 1.0);
    normal_distribution<double> normal(0.0, 1.0);
}

double Random::rand(){
    return uniform(gen); 
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
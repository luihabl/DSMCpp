#include <species.h>

#include <matrix.h>

using namespace DSMCpp;

Species::Species(double _mass, int _np_max) {

    mass = _mass;
    np = 0;

    x = DoubleMat::zeros(_np_max);
    y = DoubleMat::zeros(_np_max);
    z = DoubleMat::zeros(_np_max);

    vx = DoubleMat::zeros(_np_max);
    vy = DoubleMat::zeros(_np_max);
    vz = DoubleMat::zeros(_np_max);
}

void Species::add_n_uniform_uniform(int n, double vmin, double vmax) {

}

void Species::add_n_uniform_maxwellian(int n, double temperature) {

}
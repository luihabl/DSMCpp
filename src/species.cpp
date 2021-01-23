#include <species.h>

#include <matrix.h>
#include <rand.h>
#include <const.h>
#include <par.h>

using namespace DSMCpp;

Species::Species(Parameters * _par) {

	par = _par;

    mass = par->mass;
    np = 0;

    x  = DoubleMat::zeros(par->np_max);
    y  = DoubleMat::zeros(par->np_max);
    z  = DoubleMat::zeros(par->np_max);

    vx = DoubleMat::zeros(par->np_max);
    vy = DoubleMat::zeros(par->np_max);
    vz = DoubleMat::zeros(par->np_max);

}

void Species::add_n_uniform_uniform(int n, double vmin, double vmax) {
	double lx = par->lx;
	double ly = par->ly;

	for (size_t i = np; i < np + n; i++)
	{
		x.m[i]  = lx * Random::rand();
		y.m[i]  = ly * Random::rand();
		z.m[i]  = 0.0;
		vx.m[i] = Random::rand(vmin, vmax);
		vy.m[i] = Random::rand(vmin, vmax);
		vz.m[i] = Random::rand(vmin, vmax);
	}
	np += n;
}

void Species::add_n_uniform_maxwellian(int n, double temperature) {
    
    double v_temperature = sqrt(Const::k_boltz * temperature / mass);
	double lx = par->lx;
	double ly = par->ly;

	for (size_t i = np; i < np + n; i++)
	{
		x.m[i]  = lx * Random::rand();
		y.m[i]  = ly * Random::rand();
		z.m[i]  = 0.0;
		vx.m[i] = Random::randn(0.0, v_temperature);
		vy.m[i] = Random::randn(0.0, v_temperature);
		vz.m[i] = Random::randn(0.0, v_temperature);
	}
	np += n;

}
#include <species.h>

#include <matrix.h>
#include <rand.h>
#include <const.h>
#include <par.h>

using namespace DSMCpp;

Species::Species(Parameters * _par) : ParametricObj(_par) {
	
    mass = par->mass;
	pw = par->pw;
    np = 0;

    x  = DoubleMat::zeros(par->np_max);
    y  = DoubleMat::zeros(par->np_max);
    z  = DoubleMat::zeros(par->np_max);

    vx = DoubleMat::zeros(par->np_max);
    vy = DoubleMat::zeros(par->np_max);
    vz = DoubleMat::zeros(par->np_max);

}

DoubleMat Species::get_state_vector() {
	DoubleMat state_vector = DoubleMat::zeros(np, 6);
    for (int i=0; i<np; i++){
        state_vector.m[i * 6 + 0] = x.m[i];
        state_vector.m[i * 6 + 1] = y.m[i];
        state_vector.m[i * 6 + 2] = z.m[i];
        state_vector.m[i * 6 + 3] = vx.m[i];
        state_vector.m[i * 6 + 4] = vy.m[i];
        state_vector.m[i * 6 + 5] = vz.m[i];
    }
	return state_vector;
}

void Species::add_n_uniform_uniform(int n, double vmin, double vmax) {
	double lx = par->lx;
	double ly = par->ly;

	for (int i = np; i < np + n; i++)
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

	for (int i = np; i < np + n; i++)
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

void Species::add_n_uniform_equal(int n, double energy) {
    
    double v = sqrt(2 * energy * Const::e / (2 * mass));
	double lx = par->lx;
	double ly = par->ly;

	for (int i = np; i < np + n; i++)
	{
		x.m[i]  = lx * Random::rand();
		y.m[i]  = ly * Random::rand();
		z.m[i]  = 0.0;
		vx.m[i] = v;
		vy.m[i] = v;
		vz.m[i] = 0;
	}
	np += n;
}

void Species::move() {
	double dt = par->dt;
	for (int i = 0; i < np; i++) {
		x.m[i] = x.m[i] + dt * vx.m[i];
		y.m[i] = y.m[i] + dt * vy.m[i];
	}
}
#include <simulation.h>

#include <string>
#include <log.h>
#include <par.h>
#include <bound.h>

using namespace DSMCpp;

Simulation::Simulation(Parameters * _par) {
    par = _par;
}

void Simulation::setup() {
    
    step = 0;

    //Add TMatrix<Species> afterwards
    s = Species(par);
    s.add_n_uniform_maxwellian(par->np_add, par->temperature);

    bound = Boundaries(par);
}

void Simulation::run() {
    Log::print("Starting main loop");
    while(step < par->n_steps) iterate();
    Log::print("Finished main loop");   
}

void Simulation::iterate() {
    s.move();
    bound.collisions(&s);
    step += 1;
}

#include <simulation.h>

#include <string>
#include <log.h>
#include <par.h>
#include <bound.h>

using namespace DSMCpp;

void Simulation::setup() {
    step = 0;

    s = Species(par); //Add TMatrix<Species> afterwards
    s.add_n_uniform_maxwellian(par->np_add, par->temperature);
    
    bound = Boundaries(par);
    
    mesh = Mesh(par);
}

void Simulation::run() {
    Log::print("Starting main loop");
    while(step < par->n_steps) iterate();
    Log::print("Finished main loop");   
}

void Simulation::iterate() {
    s.move();

    //Particle collisions


    bound.collisions(&s);
    step += 1;
}

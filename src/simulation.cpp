#include <simulation.h>

#include <string>
#include <log.h>
#include <par.h>

using namespace DSMCpp;

Simulation::Simulation(Parameters * _par) {
    par = _par;
}

void Simulation::run() {
    for(step=0; step < par->n_steps; step++) {
        Log::print("step " + std::to_string(step));
        

    }
}

#include <simulation.h>

#include <string>
#include <log.h>
#include <par.h>
#include <bound.h>
#include <coll.h>
#include <iostream>
#include <io.h>

using namespace DSMCpp;

void Simulation::setup() {
    step = 0;

    s = Species(par); //Add TMatrix<Species> afterwards
    s.add_n_uniform_maxwellian(par->np_add, par->temperature);
    
    bound = BoundaryHandler(par);
    
    mesh = Mesh(par);

    coll = CollisionHandler(par);
}

void Simulation::run() {
    Log::print("Starting main loop");
    while(step < par->n_steps) iterate();
    Log::print("Finished main loop");   
    save_output();
}

void Simulation::iterate() {
    s.move();
    bound.collide(&s);
    coll.collide(&s);
    step += 1;
}

void Simulation::save_output() {
    Output::save_to_csv("x.csv", &s.x, s.np);
    Output::save_to_csv("y.csv", &s.y, s.np);
    Output::save_to_csv("z.csv", &s.z, s.np);
    Output::save_to_csv("vx.csv", &s.vx, s.np);
    Output::save_to_csv("vy.csv", &s.vy, s.np);
    Output::save_to_csv("vz.csv", &s.vz, s.np);
}

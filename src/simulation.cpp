#include <simulation.h>

#include <string>
#include <log.h>
#include <par.h>
#include <bound.h>
#include <coll.h>
#include <iostream>

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

    for (auto const& cell : s.cmap) {
        cout << cell.first << ": ";
        for (IntNode * n = cell.second.head; n != nullptr; n=n->next) {
            
            std::cout << n->data << " ";
        }
        std::cout << std::endl;
    }

}

void Simulation::iterate() {
    s.move();
    bound.collide(&s);
    coll.collide(&s);
    step += 1;
}

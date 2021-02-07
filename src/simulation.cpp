#include <simulation.h>

#include <string>
#include <chrono>
#include <log.h>
#include <par.h>
#include <bound.h>
#include <coll.h>
#include <io.h>

using namespace DSMCpp;
using namespace std::chrono;

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
    save_state();
}

void Simulation::iterate() {
    high_resolution_clock::time_point t1 = high_resolution_clock::now();
    
    s.move();
    bound.collide(&s);
    coll.collide(&s);
    step += 1;
    
    high_resolution_clock::time_point t2 = high_resolution_clock::now();
    duration<double, std::milli> time_span = t2 - t1;
    print_loop_info(time_span.count());
}

void Simulation::save_state() {;
    Output::save_to_npy("state.npy", s.get_state_vector());
}

void Simulation::print_loop_info(double loop_time) {
    Log::print("Step: " + to_string(step) + "/" + to_string(par->n_steps) + " Loop time: " + to_string(loop_time) + " ms");
}

#include <simulation.h>

#include <string>
#include <chrono>
#include <log.h>
#include <par.h>
#include <bound.h>
#include <coll.h>
#include <io.h>
#include <const.h>
#include <rand.h>
#include <num.h>

using namespace DSMCpp;
using namespace std::chrono;

void Simulation::setup() {
    
    Random::init(par->seed);
    
    step = 0;
    s = Species(par); //Add TMatrix<Species> afterwards
    // s.add_n_uniform_maxwellian(par->np_add, par->temperature);
    s.add_n_uniform_equal(par->np_add, par->temperature * (3 * Const::k_boltz / (2 * Const::e)));
    bound = BoundaryHandler(par);
    mesh = Mesh(par);
    coll = CollisionHandler(par);

    TableTrig::init();
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

void Simulation::save_state() {
    #ifdef NPY_OUTPUT
    Output::save_to_npy("state.npy", s.get_state_vector());
    #else
    Output::save_to_csv("state.csv", s.get_state_vector());
    #endif
}

void Simulation::print_loop_info(double loop_time) {
    Log::print("Step: " + to_string(step) + "/" + to_string(par->n_steps) + " Loop time: " + to_string(loop_time) + " ms");
}

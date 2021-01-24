#include <log.h>
#include <simulation.h>
#include <par.h>

using namespace std;
using namespace DSMCpp;

int main() {
    Log::print("Starting DSMCpp");

    Parameters par;    
    Simulation sim(&par);

    sim.setup();
    sim.run();

    return 0;
}
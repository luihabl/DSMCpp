#include <log.h>
#include <simulation.h>
#include <par.h>
#include <io.h>

using namespace std;
using namespace DSMCpp;

int main() {
    Log::print("Starting DSMCpp");

    ConfigFile config("../config.json");
    Parameters par(&config);    
    Simulation sim(&par);

    sim.setup();
    sim.run();
    
    return 0;
}
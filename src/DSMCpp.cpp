#include <log.h>
#include <simulation.h>
#include <par.h>
#include <io.h>

using namespace std;
using namespace DSMCpp;

#ifndef DEFAULT_CONFIG_PATH
#define DEFAULT_CONFIG_PATH "config.json"
#endif

int main(int argc, char *argv[]) {
    Log::print("Starting DSMCpp");
    
    ConfigFile config(DEFAULT_CONFIG_PATH, argc, argv);
    Parameters par(&config);    
    Simulation sim(&par);

    sim.setup();
    sim.run();
    
    return 0;
}
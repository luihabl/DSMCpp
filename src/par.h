#pragma once 


// TODO: Set parameters from a config file
namespace DSMCpp {
    struct Parameters {

        Parameters(){ };

        // Geometry
        double lx = 0.1;
        double ly = 0.1;
        
        //Sim
        double dt = 0.1;
        int nx = 10;
        int ny = 10;
        int np_max = 1e5;

        //Species
        double mass = 2.1801714e-25;
    };
}
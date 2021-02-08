# DSMCpp
Simple DSMC simulation code written in C++. 

## Building
You need C++11+ and CMake 3.12+. To build, you can run the common CMake commands from the project's root:

```
mkdir build && cd build
cmake ..
cmake --build .
```
CMake will automatically fetch and download from github the necessary dependencies using  `FetchContent`. 

### Dependencies 

- [llohse/libnpy](https://github.com/llohse/libnpy) for saving output as `.npy` files
- [nlohmann/json](https://github.com/nlohmann/json) for loading JSON config files
- [cslarsen/mersenne-twister](https://github.com/cslarsen/mersenne-twister) for random number generation, since it is considerably faster than the standard library implementation

## Using the code

After building you can change the simulation parameters in the [config file](config.json). To specify the path for the config file used, you can either modify the variable `DEFAULT_CONFIG_PATH` in the [cmake file](CMakeLists.txt) or pass the path as an argument when executing the binary: 

```
./DSMCpp path/to/config.json
```
For the moment, to change some initial conditions, it is necessary to modify the code (more specifically the function `void Simulation::init()` in `simulation.cpp`) and compile it again. However in the future this will be configurable in the input file.  

The output files are saved to the same directory as the binary. The output can be saved either as a `.csv` or `.npy`. By default the code saves in `.npy`; however, to save in `.csv` you can remove the `NPY_OUTPUT` definition from the [cmake file](CMakeLists.txt).

## Notes
- For the moment it simulates a cartesian rectangular domain with reflective walls. 
- In the future, I will add the possibility for other geometries, boundary conditions and intial conditions. 
- I will also add the possibility of adding different run-time diagnostics and saving the output in different times. 

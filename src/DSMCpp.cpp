#include <iostream>
#include <log.h>

#include <rand.h>

using namespace std;
using namespace DSMCpp;

int main() {
    Log::print("Starting DSMCpp");

    cout << Random::rand() << endl;

    return 0;
}
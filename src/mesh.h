#pragma once

#include <par.h>
#include <matrix.h>

namespace DSMCpp {
    class Mesh : public ParametricObj {
        public:
            Mesh() = default;
            Mesh(Parameters * _par);
            void setup();

            int nx, ny, lx, ly, dx, dy;
            double volume;
            DoubleMat x, y;
    };
}
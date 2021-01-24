#include <mesh.h>
#include <matrix.h>
#include <par.h>

using namespace DSMCpp;

Mesh::Mesh(Parameters * _par) {
    par = _par;
    nx = par->nx;
    ny = par->ny;
    lx = par->lx;
    ly = par->ly;

    x = DoubleMat::zeros(nx);
    y = DoubleMat::zeros(ny);

    setup();
}

void Mesh::setup() {
    dx = lx / ((double) nx - 1);
    dy = ly / ((double) ny - 1);

    for(int i=0; i<nx; i++) x.m[i] = dx * (double) i;
    for(int i=0; i<ny; i++) y.m[i] = dy * (double) i;

    volume = dx*dy;
}
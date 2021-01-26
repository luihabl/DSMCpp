#include <coll.h>
#include <species.h>
#include <unordered_map>
#include <math.h>
#include <llist.h>
#include <const.h>
#include <rand.h>

using namespace DSMCpp;

CollisionHandler::CollisionHandler(Parameters * _par) : ParametricObj(_par) {
    sigma_vr_max = par->sigma * 2 * sqrt(Const::k_boltz * par->temperature / par->mass);
}

void CollisionHandler::update_map(Species * s) {

    s->cmap.clear();

    int cx, cy;
    int ny = par->ny;
    double dx = par->lx / ((double) par->nx - 1);
    double dy = par->ly / ((double) par->ny - 1);
    for (int i=0; i<s->np; i++) {
        cx = (int) floor(s->x.m[i] / dx);
        cy = (int) floor(s->y.m[i] / dy);
        // try { s->cmap[cx * ny + cy].add(i); }
        // catch (int e) {
        //     s->cmap[cx * ny + cy] = LinkedList<int>();
        //     s->cmap[cx * ny + cy].add(i);
        // }
        if (s->cmap.count(cx * ny + cy) == 0) s->cmap[cx * ny + cy] = LinkedList<int>();
        s->cmap[cx * ny + cy].add(i);
    }

}

void CollisionHandler::collide(Species * s) {
    update_map(s);
    ntc_collisions(s);
}

void CollisionHandler::ntc_collisions(Species * s) {
        
    const double vc = par->dx * par->dy;
    const double dt = par->dt;
    const double pw = par->pw;
    const double sigma = par->sigma;
    double sigma_vr, sigma_vr_max_tmp=sigma_vr_max;

    int p1_index, p1_cmap_index, p2_index, p2_cmap_index;
    double vrx, vry, vrz, vr;

    double nc_ntc; int nc;
    double np_cell, n_coll;
    

    for (auto const& cell : s->cmap) {
        n_coll = 0;
        np_cell = cell.second.size;
        nc_ntc =  0.5 * np_cell * (np_cell - 1) * pw * sigma_vr_max * dt / vc;
        nc = floor(nc_ntc + 0.5);

        for(int i=0; i<nc; i++) {

            p1_cmap_index = floor(np_cell * Random::rand());
            do {p2_cmap_index = floor(np_cell * Random::rand());}
            while(p1_cmap_index==p2_cmap_index);

            p1_index = cell.second.get(p1_cmap_index);
            p2_index = cell.second.get(p2_cmap_index);

            vrx = s->vx.m[p1_index] - s->vx.m[p2_index];
            vry = s->vy.m[p1_index] - s->vy.m[p2_index];
            vrz = s->vz.m[p1_index] - s->vz.m[p2_index];
            vr = sqrt(vrx*vrx + vry*vry + vrz*vrz);

            sigma_vr = sigma * vr;
            sigma_vr_max_tmp = sigma_vr > sigma_vr_max_tmp ? sigma_vr : sigma_vr_max_tmp;

            if ((sigma_vr / sigma_vr_max) > Random::rand()) {
                //isotropic_collision(p1_index, p2_index);
                n_coll++;
            }

        }

        if(n_coll>0) sigma_vr_max = sigma_vr_max_tmp;
    }
}   
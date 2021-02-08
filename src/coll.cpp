#include <coll.h>
#include <species.h>
#include <unordered_map>
#include <math.h>
#include <num.h>
#include <const.h>
#include <rand.h>
#include <log.h>
#include <vector>


using namespace DSMCpp;

CollisionHandler::CollisionHandler(Parameters * _par) : ParametricObj(_par) {
    sigma_vr_max = par->sigma * 2 * sqrt(Const::k_boltz * par->temperature / par->mass);
    TableTrig::init();
}

void CollisionHandler::update_map(Species * s) {

    cmap.clear();

    int cx, cy;
    int ny = par->ny;
    double dx = par->lx / ((double) par->nx - 1);
    double dy = par->ly / ((double) par->ny - 1);
    for (int i=0; i<s->np; i++) {
        cx = (int) floor(s->x.m[i] / dx);
        cy = (int) floor(s->y.m[i] / dy);
        cmap[cx * ny + cy].push_back(i);
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

    int cmap_size = cmap.size();
    IntMat keys(cmap_size);
    int i = 0;
    for (auto const& cell : cmap){
        keys.m[i] = cell.first;
        i += 1;
    }

    for (int j=0; j < cmap_size; j++) {
        
        int p1_cmap_index, p2_cmap_index;

        std::vector<int> *cell = &cmap[keys.m[j]];

        int n_coll = 0;
        double np_cell = cell->size();
        double nc_ntc =  0.5 * np_cell * (np_cell - 1) * pw * sigma_vr_max * dt / vc;
        int nc = floor(nc_ntc + 0.5);
        
        for(int i=0; i<nc; i++) {

            p1_cmap_index = 0;
            p2_cmap_index = 0;

            p1_cmap_index = Random::rand_int_zero(np_cell);
            do {p2_cmap_index = Random::rand_int_zero(np_cell);}
            while(p1_cmap_index==p2_cmap_index);

            int p1_index = (*cell)[p1_cmap_index];
            int p2_index = (*cell)[p2_cmap_index];

            double v1x = s->vx.m[p1_index];
            double v1y = s->vy.m[p1_index]; 
            double v1z = s->vz.m[p1_index];
            double v2x = s->vx.m[p2_index];
            double v2y = s->vy.m[p2_index]; 
            double v2z = s->vz.m[p2_index];

            double vrx = v1x - v2x;
            double vry = v1y - v2y;
            double vrz = v1z - v2z;
            double vr = sqrtf(vrx*vrx + vry*vry + vrz*vrz);

            sigma_vr = sigma * vr;
            sigma_vr_max_tmp = sigma_vr > sigma_vr_max_tmp ? sigma_vr : sigma_vr_max_tmp;

            double rand = Random::rand();
            if ((sigma_vr / sigma_vr_max) > rand) {
                isotropic_elastic_scattering(s, p1_index, p2_index, vr, v1x, v1y, v1z, v2x, v2y, v2z);
                n_coll++;
            }
        }

        if(n_coll>0) sigma_vr_max = sigma_vr_max_tmp;
    }
}

void CollisionHandler::isotropic_elastic_scattering(Species * s, const int & p1_index, const int & p2_index, const double & vr, 
        const double & v1x, const double & v1y, const double & v1z,
        const double & v2x, const double & v2y, const double & v2z) {
    
    double phi = 2 * Const::pi * Random::rand(); 
    double cos_theta = 2 * Random::rand() - 1;
    double sin_theta = sqrtf(1 - cos_theta * cos_theta); 

    double vrx2 = vr * cos_theta;
    double vry2 = vr * sin_theta * TableTrig::fcos(phi);
    double vrz2 = vr * sin_theta * TableTrig::fsin(phi); 

    double vcmx = 0.5 * (v1x + v2x);
    double vcmy = 0.5 * (v1y + v2y);
    double vcmz = 0.5 * (v1z + v2z);

    s->vx.m[p1_index] = vcmx + 0.5 * vrx2;
    s->vy.m[p1_index] = vcmy + 0.5 * vry2;
    s->vz.m[p1_index] = vcmz + 0.5 * vrz2;

    s->vx.m[p2_index] = vcmx - 0.5 * vrx2;
    s->vy.m[p2_index] = vcmy - 0.5 * vry2;
    s->vz.m[p2_index] = vcmz - 0.5 * vrz2;
}
#include <coll.h>
#include <species.h>
#include <unordered_map>
#include <math.h>
// #include <llist.h>
#include <const.h>
#include <rand.h>

#include <log.h>
#include <chrono>
// #include <cstdlib>

using namespace DSMCpp;

CollisionHandler::CollisionHandler(Parameters * _par) : ParametricObj(_par) {
    sigma_vr_max = par->sigma * 10 * sqrt(Const::k_boltz * par->temperature / par->mass);
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
        // try { s->cmap[cx * ny + cy].add(i); }
        // catch (int e) {
        //     s->cmap[cx * ny + cy] = LinkedList<int>();
        //     s->cmap[cx * ny + cy].add(i);
        // }
        // if (cmap.count(cx * ny + cy) == 0) cmap[cx * ny + cy] = LinkedList<int>();
        // cmap[cx * ny + cy].add(i);
        int s = cmap[cx * ny + cy].size();
        cmap[cx * ny + cy][s] = i;

    }

}

void CollisionHandler::collide(Species * s) {
    update_map(s);
    ntc_collisions(s);
}

using namespace std::chrono;
void CollisionHandler::ntc_collisions(Species * s) {
        
    const double vc = par->dx * par->dy;
    const double dt = par->dt;
    const double pw = par->pw;
    const double sigma = par->sigma;
    double sigma_vr, sigma_vr_max_tmp=sigma_vr_max;

    int p1_index, p1_cmap_index, p2_index, p2_cmap_index;
    double vrx, vry, vrz, vr;

    double nc_ntc, np_cell; 
    int nc, n_coll;

    high_resolution_clock::time_point t1 = high_resolution_clock::now();

    for (auto const& cell : cmap) {
        n_coll = 0;
        np_cell = cell.second.size();
        nc_ntc =  0.5 * np_cell * (np_cell - 1) * pw * sigma_vr_max * dt / vc;
        nc = floor(nc_ntc + 0.5);
        
        for(int i=0; i<nc; i++) {

            p1_cmap_index = floor(np_cell * Random::rand());
            // p1_cmap_index = rand() % (int) np_cell;
            do {p2_cmap_index = floor(np_cell * Random::rand());}
            // do {p2_cmap_index = rand() % (int) np_cell;}
            while(p1_cmap_index==p2_cmap_index);

            // p1_index = cell.second.at(p1_cmap_index);
            // p2_index = cell.second.at(p2_cmap_index);

            // vrx = s->vx.m[p1_index] - s->vx.m[p2_index];
            // vry = s->vy.m[p1_index] - s->vy.m[p2_index];
            // vrz = s->vz.m[p1_index] - s->vz.m[p2_index];
            // vr = sqrt(vrx*vrx + vry*vry + vrz*vrz);

            // sigma_vr = sigma * vr;
            // sigma_vr_max_tmp = sigma_vr > sigma_vr_max_tmp ? sigma_vr : sigma_vr_max_tmp;

            // double rand = Random::rand();
            // if ((sigma_vr / sigma_vr_max) > rand) {
            //     isotropic_elastic_scattering(s, p1_index, p2_index, vr);
            //     n_coll++;
            // }
        }

        if(n_coll>0) sigma_vr_max = sigma_vr_max_tmp;
    }
    high_resolution_clock::time_point t2 = high_resolution_clock::now();
    duration<double, std::milli> time_span = t2 - t1;
    std::cout << "It took me " << time_span.count() << " milliseconds." << std::endl;
}

void CollisionHandler::isotropic_elastic_scattering(Species * s, const int & p1_index, const int & p2_index, const double & vr) {
    
    double phi = 2 * M_PI * Random::rand(); 
    double cos_theta = 2 * Random::rand() - 1;
    double sin_theta = sqrt(1 - cos_theta * cos_theta); 

    double vrx2 = vr * cos_theta;
    double vry2 = vr * sin_theta * cos(phi);
    double vrz2 = vr * sin_theta * sin(phi); 

    double vcmx = 0.5 * (s->vx.m[p1_index] + s->vx.m[p2_index]);
    double vcmy = 0.5 * (s->vy.m[p1_index] + s->vy.m[p2_index]);
    double vcmz = 0.5 * (s->vz.m[p1_index] + s->vz.m[p2_index]);

    s->vx.m[p1_index] = vcmx + 0.5 * vrx2;
    s->vy.m[p1_index] = vcmy + 0.5 * vry2;
    s->vz.m[p1_index] = vcmz + 0.5 * vrz2;

    s->vx.m[p2_index] = vcmx - 0.5 * vrx2;
    s->vy.m[p2_index] = vcmy - 0.5 * vry2;
    s->vz.m[p2_index] = vcmz - 0.5 * vrz2;
}
#include <coll.h>
#include <species.h>
#include <unordered_map>
#include <math.h>
#include <llist.h>

using namespace DSMCpp;

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
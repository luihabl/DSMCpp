#include <bound.h>

using namespace DSMCpp;

void Boundaries::collisions(Species * s) {
    // Other boundary methods will be added here in the future
    collisions_outer_walls(s);
}

void Boundaries::collisions_outer_walls(Species * s) {
    double x, y, vx, vy;
    double lx = par->lx;
    double ly = par->ly;
    
    for (int i = 0; i < s->np; i++) {
        x  = s->x.m[i]; vx = s->vx.m[i];
        y  = s->y.m[i]; vy = s->vy.m[i];
    
        if (x < lx && x > 0 && y < ly && y > 0) continue;

        if (x < 0) {
            s->x.m[i] = -x;
            s->vx.m[i] = -vx; 
        }

        if (y < 0) {
            s->y.m[i] = -y;
            s->vy.m[i] = -vy; 
        }

        if (x > lx) {
            s->x.m[i] = 2*lx - x;
            s->vx.m[i] = -vx; 
        }

        if (y > ly) {
            s->y.m[i] = 2*ly - y;
            s->vy.m[i] = -vy; 
        }

    }

}
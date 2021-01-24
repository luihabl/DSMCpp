#include <bound.h>

using namespace DSMCpp;

void Boundaries::collisions(Species * s) {
    double x, y, vx, vy;
    
    for (int i = 0; i < s->np; i++) {
        x  = s->x.m[i]; vx = s->vx.m[i];
        y  = s->y.m[i]; vy = s->vy.m[i];
    
        if (x < par->lx && x > 0 && y < par->ly && y > 0) continue;


        
    }

}
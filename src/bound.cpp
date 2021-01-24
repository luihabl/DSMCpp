#include <bound.h>

using namespace DSMCpp;

void Boundaries::collisions(Species * s) {
    // Other boundary methods will be added here in the future
    collisions_outer_walls(s);
}

void Boundaries::collisions_outer_walls(Species * s) {
    double x, y;
    double lx = par->lx;
    double ly = par->ly;
    
    for (int i = 0; i < s->np; i++) {
        x  = s->x.m[i]; y  = s->y.m[i];
    
        if (x < lx && x > 0 && y < ly && y > 0) continue;

        if (x < 0) {
            specular_reflection(s, i, 0, 0);
        }

        if (y < 0) {
            specular_reflection(s, i, 1, 0);
        }

        if (x > lx) {
            specular_reflection(s, i, 0, lx);
        }

        if (y > ly) {
            specular_reflection(s, i, 1, ly);
        }
    }
}

void Boundaries::specular_reflection(Species * s, int index, int nbound, double lbound) {
    // Boundary number: 0: x, 1: y

	switch(nbound){
		case 0:
			s->x.m[index] = 2*lbound - s->x.m[index];
            s->vx.m[index] = -s->vx.m[index];
			break;
		
		case 1:
			s->y.m[index] = 2*lbound - s->y.m[index];
            s->vy.m[index] = -s->vy.m[index];
			break;

		default:
			break;
	}

}
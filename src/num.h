#pragma once

#include <math.h>
#include <matrix.h>
#include <const.h>

#define MAX_CIRCLE_ANGLE 1024
#define HALF_MAX_CIRCLE_ANGLE (MAX_CIRCLE_ANGLE/2)
#define QUARTER_MAX_CIRCLE_ANGLE (MAX_CIRCLE_ANGLE/4)
#define MASK_MAX_CIRCLE_ANGLE (MAX_CIRCLE_ANGLE - 1)

using namespace DSMCpp;

namespace TableTrig{

   DoubleMat cossin_table = DoubleMat::zeros(MAX_CIRCLE_ANGLE);

   inline void init() {
      for (int i = 0 ; i < MAX_CIRCLE_ANGLE ; i++) {
         cossin_table.m[i] = sin((double)i * Const::pi / HALF_MAX_CIRCLE_ANGLE);
      }
   }

   inline double fcos(double x) {
      int i = (int) (x * HALF_MAX_CIRCLE_ANGLE / Const::pi);
      if (i < 0) return cossin_table.m[((-i) + QUARTER_MAX_CIRCLE_ANGLE)&MASK_MAX_CIRCLE_ANGLE];
      else return cossin_table.m[(i + QUARTER_MAX_CIRCLE_ANGLE)&MASK_MAX_CIRCLE_ANGLE];
   }
   
   inline double fsin(double x) {
      int i = (int) (x * HALF_MAX_CIRCLE_ANGLE / Const::pi);
      if (i < 0) return cossin_table.m[(-((-i)&MASK_MAX_CIRCLE_ANGLE)) + MAX_CIRCLE_ANGLE];
      else return cossin_table.m[i&MASK_MAX_CIRCLE_ANGLE];
   }


}
#ifndef AVANZAR_H
#define AVANZAR_H

#include "math.h"

// Declaracion de funciones

int first_step(float *x, float *v, float *f, int N);
int second_step(float *v, float *f, int N);
int apply_PBC(float *x,float L, int N);
#endif

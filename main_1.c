#include "general.h"
#include "interaccion.h"
#include "inicializar.h"
#include "avanzar.h"
#include "visualizacion.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int main(int argc, char *argv[]){

  // Definicion del main



//------------------ MAIN DE EJEMPLO PARA VISUALIZAR CON VMD ------------------//
  int N = 100;
  float L = 10, dx = 0.05;
  float *x = (float *) malloc(3*N*sizeof(float));
  float *v = (float *) malloc(3*N*sizeof(float));

  // El formato del filename ".lammpstrj", ese VMD lo lee comodamente
  char filename[255];
  sprintf(filename, "prueba.lammpstrj");
  int N_frames = 100;

// Armo un boomerang con un """""movimiento browniano"""""
  for(int i = 0; i < 3*N; i++){
    x[i] = x[i] + L*rand()/RAND_MAX; // Estado inicial random en la caja
    v[i] = 0.0;
  }
  for(int l = 0; l < N_frames; l++){
    for(int i = 0; i < 3*N; i++){
      x[i] = x[i] + dx*(2.0*rand()/RAND_MAX-1.0); // Genero perturbacion random
    }
    save_lammpstrj(filename, x, v, N, L, l);  // La guardo (append para 0<l)
  }
  // Hago la vuelta del boomerang
  for(int l = 0; l < N_frames; l++){
    load_lammpstrj(filename, x, v, N, &L, N_frames-1-l); // Cargo estado viejo
    save_lammpstrj(filename, x, v, N, L, N_frames+l);    // Lo guardo (append)
  }
  free(x);
  free(v);
// Capaz notaron que las velocidades estan al pedo, nos va a servir guardarlas
// para tener checkpoints de estados bien termalizados.
// Checkpoint is love, checkpoint is life
//-----------------------------------------------------------------------------//

  return 0;
}

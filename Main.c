#include "general.h"
#include "inicializar.h"
#include "avanzar.h"
#include "visualizacion.h"
#include "interacciones.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int main()
{
	srand(time(NULL));
	FILE * fp;
	float rd=0;

 	char filename[255];
 	sprintf(filename, "Inicio.lammpstrj");

	
	rd=random_();
//	printf("%f \n",rd);
	float g=0;
	int n=10;
	double *tabla_fz_pot;
	tabla_fz_pot=(double *)malloc(3*n*sizeof(double));
	armado_tabla(n,tabla_fz_pot);
//	imprimirMat(tabla_fz_pot,n,3);
	//printf("%d %d %d \n",*(tabla_fz_pot);
//	float n;
//	n=norma(2,1,1,1,3);
//	printf("%f",n);
	float L=2;
	float T=0.7;
	float *x;
	int N=27;
 	printf("%f ",T); 

	n=cbrt(N);
	//printf("%d ",n);
	x=(float *)malloc(3*N*sizeof(float));
	set_box(x,N,L);

	//imprimirMat(x,N,3);
	


	float *v;	
	v=(float *)malloc(3*N*sizeof(float));
	set_v(v,N,T);
	//for (int k=0;k<N;k++)
	//{
	//fprintf(fp,"%f ",*(v+k*3));		
	//}
	//fclose(fp);
	//imprimirMat(v,N,3);
	save_lammpstrj(filename, x, v, N, L, 0);  // La guardo (append para 0<l)
	//free(v);
	//free(x);
return 0;
}

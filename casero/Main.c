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

	int n=100000; //es para el refinamiento de las tablas
	int N= 512;//512; //numero de particulas
	//para que rho=N/L^3 =0.8442 -> L=8.4646


/*
	FILE *fp2;
	char filename2[64];
 	sprintf(filename2, "presiones.txt");
	fp2= fopen(filename2,	"a");
*/	double p;

	double *tabla_fz_pot;
	tabla_fz_pot=(double *)malloc(3*n*sizeof(double));

	double *f;
	f=(double *)malloc(N*3*sizeof(double));
	//seteo en 0 las fuerzas
	for(int k=0;k<3*N;k++)
	{
	*(f+k)=0;
	}

	double h=0.001;
	armado_tabla(n,tabla_fz_pot);

	double *x;
	x=(double *)malloc(3*N*sizeof(double));
	double *v;
	v=(double *)malloc(3*N*sizeof(double));

	for(float rho=0.4; rho<0.9;rho+=0.1)
	{
	float L=pow(N/rho,1.0/3.0);
	float T=2;
	//printf("%lf",L);

	char filename1[255];
 	sprintf(filename1, "rho=%lf_N=%d.lammpstrj",rho,N); //

	FILE *fp;
	char filename[64];
 	sprintf(filename, "rho=%lf_N=%d.txt",rho,N);
	fp= fopen(filename,	"w");

	set_box(x,N,L);
	set_v(v,N,T);

	save_lammpstrj(filename1, x, v, N, L, 0);

	double u_n;
	double e_c;
	double temps=2;
	double lambda=0.95;
//	double ro = N/(L*L*L);
//	double p=ro*N*T;
//	double u_t=0; //energia total por numero de particula
	for (T=2;T>0.4;T-=0.03)
	{
		double temp_prom=0;
		for (int i=0;i<3000;i++)
		{

			u_n=verlet(x,v,f,L,N, n,tabla_fz_pot,h,&p);


			save_lammpstrj(filename1, x, v, N, L, i);
			//u_t+=u_n;

			e_c= energia_k(v,N);

			temps= (double) (2*e_c)/(3*N);
			temp_prom+=temps/3000;

			fprintf(fp,"%lf ", temps);
			fprintf(fp,"%lf ", e_c);
			fprintf(fp,"%lf ", u_n);
			fprintf(fp,"%lf ", T);
			fprintf(fp,"%lf \n", p);

		}
		printf("%lf %lf \n ",temp_prom,T);
		rescaling(v,T-0.03,temp_prom,N);




//	fprintf(fp3,"%lf ", p);

	}
	fclose(fp);
	}
//	fclose(fp3);

	//free(v);
	//free(x);
return 0;
}

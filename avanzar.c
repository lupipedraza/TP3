#include "general.h"
#include "interaccion.h"
#include "avanzar.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

// Definicion de funciones

int first_step(float *x, float *v, float *f, int N)
{
	float h=0.01;
	float m=1;
	for( int i=0;i<3*N;i++)
		{
		*(x+i)=*(x+i)+*(v+i)*h+*(f+i)*h*h/(2*m);
		*(v+i)=*(v+i)+*(f+i)*h/(2*m);//en realidad es v(t+h/2) 
		}
	return 0;
}

int second_step(float *v, float *f, int N)
{
	float h=0.01;
	float m=1;
	for( int i=0;i<3*N;i++)
		{
		*(v+i)=*(v+i)+*(f+i)*h/(2*m);//en realidad es v(t+h/2) 
		}
	return 0;
}

int apply_PBC(float *x,float L, int N)
{
	for( int i=0;i<3*N;i++)
	{
		if(*(x+i)<0)
			*(x+i)+=L;
		if(*(x+i)>L)
			*(x+i)-=L;
	}
	return 0;
}



int verlet(float *x, float *v, float *f, float L, int N)
{
	first_step(x, v, f, N);
	apply_PBC(x,L,N);
	//fuerzas(x,f,L,Lut_V,Lut_F,N);
	second_step(v, f, N);
	return 0;

}
	

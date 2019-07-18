
#include "general.h"



float random_()
{

	return (float)rand()/(float)RAND_MAX;

}

//////////////////////////

float Gaussiana (float mu,float sigma)
{
	int n=10;
	float z=0;
	for (int i=0;i<n;i++)
	{ z+=random_();
	}
	z=(float)(z/(float)n-0.5)*sqrt(12.0*(float)n);

	return z*sigma+mu;
}

////////////////////////

double norma_2(double x,double y,double z)
{
	double r;
	r=(x*x)+(y*y)+(z*z);
	return r;


}

/////////////////////////

// esta funcion tiene problemas. acomodar cuando hagamos las otras.

double delta_x(double x1,double x2, float L)
{

	double d;
	d=x1-x2;
	if (d>0.5*L)
	{d-= (double) L;}
	if (d<-0.5*L)
	{d+= (double) L;}

	return d;
}

///////////////////
int imprimirMat(double *red, int n,int m)
    {
        int k, l;
        for (k=0; k<n; k++)
	{
            for(l=0; l<m; l++)
            {
		printf("%lf ", *(red+m*k+l));
		}
	        printf("\n");
        }
	printf("\n");
    return 0;
    }


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
	z=(z/n-0.5)*sqrt(12);//Mirar 12??

	return z*sigma+mu;
}

////////////////////////

float norma(float x1,float y1,float x2, float y2,float L)
{
	return sqrt(pow(delta_x(x1,x2,L),2)+pow(delta_x(y1,y2,L),2));


}

/////////////////////////

// esta funcion tiene problemas. acomodar cuando hagamos las otras.

float delta_x(float x1,float x2, float L)
{
	
	float d;
	d=x1-x2;
	if (d>0.5*L)
	{d-=L;}	
	if (d<-0.5*L)
	{d+=L;}	
	
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
		printf("%d ", *(red+m*k+l));
		}
	        printf("\n");
        }
	printf("\n");
    return 0;
    }

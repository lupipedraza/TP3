#include "general.h"
#include "inicializar.h"

float set_box(double *X, int N, float L)
{
	int n;
	n=cbrt(N);
	//printf("%d ",n);
	float dl=(float)L/n;
	int i=0;
	for (int x=0; x<n; x++)
	{	for (int y=0; y<n; y++)
		{	for (int z=0; z<n; z++)
			{
			  *(X+3*i)=dl*(x+0.5);
			  *(X+(3*i)+1)=dl*(y+0.5);
			  *(X+(3*i)+2)=dl*(z+0.5);
			  i++;
			}
		}
	}

	return dl;

}

/////////////////////////

float set_v(double *V, int N, float T)
{	float s;
	s=sqrt(T);
 	for (int i=0;i<3*N;i++)
	{*(V+i)=Gaussiana(0.0,s);}
	float VCM[3]={0,0,0};

	for (int i=0;i<N;i++)
	{	for (int k=0;k<3;k++)
		{VCM[k]+=*(V+(3*i)+k)/N;}
	}
	float EC=0;

	for (int i=0;i<N;i++)
	{	for (int k=0;k<3;k++)
		{*(V+(3*i)+k)-=VCM[k];
		EC+=pow(*(V+(3*i)+k),2);
		}

	}


	return 1/2*EC;
}

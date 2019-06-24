#include "general.h"
#include "Inicializar.h"

int main()
{
	srand(time(NULL));
	FILE * fp;
	float rd=0;
	char filename[64];
		//Para guardar


	sprintf(filename,"Velx.txt");
	fp = fopen (filename, "w");
	rd=random_();
//	printf("%f \n",rd);
	float g=0;


	
//	printf("%f \n",g);
//	float n;
//	n=norma(2,1,1,1,3);
//	printf("%f",n);

	float T=0.7;
	float *x;
	int N=27;
	int n;
	n=cbrt(N);
	//printf("%d ",n);
	x=(float *)malloc(3*N*sizeof(float));
	set_box(x,N,1.0);

	//imprimirMat(x,N,3);

	float *v;	
	v=(float *)malloc(3*N*sizeof(float));
	set_v(v,N,T);
	for (int k=0;k<N;k++)
	{
	fprintf(fp,"%f ",*(v+k*3));		
	}
	fclose(fp);
	//imprimirMat(v,N,3);
	free(v);
	free(x);
return 0;
}

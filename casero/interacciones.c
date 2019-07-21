#include "interacciones.h"
#include "general.h"
#include <math.h>


//////////////////////////
int armado_tabla (int n ,double *tabla_fz_pot)
{
/*FILE *fp;
char filename[64];
sprintf(filename, "tabla_fz_pot.txt");
fp= fopen(filename,	"a");*/
double r_c = 2.5; //radio de corte
//float eps=1.0;
//float sigma=1.0;
double F_r;
double U;
double r_2;
double dr_2;
double r;
//voy a necesitar dr, r0, dr_2
dr_2=(double)(r_c*r_c/(double)n);

for (int i =0; i< n; i++){
  r_2=(double)(i+1)*dr_2;
  r=(double) 1.0/r_2;
  /*fprintf(fp, "%lf ", r_2);*/
  U=(4*(pow(r,6) - pow(r,3)))+0.0163;
  /*fprintf(fp,"%lf ", U);*/
  F_r=24*(2*pow(r, 7) - pow(r,4));//es Fr/r
  /*fprintf(fp,"%lf \n", F_r);*/
  *(tabla_fz_pot+(3*i))=r_2; //guardo el radio
  *(tabla_fz_pot+(1+(3*i)))=F_r; //guardo la fuerza
  *(tabla_fz_pot+(2+(3*i)))=U; //guardo el potencial
  }
//fclose(fp);
return dr_2;
}
//////////////////////////

double interpolar (int n, double r_2, double *tabla_fz_pot, double * F_mod)
{//le paso r_2
//n son los puntos de espaciado en mi espacio para interpolar

float r_c=2.5;
double dr_2;
int i;
double m;
double b;
double f_nueva;
double u_nueva;

//voy a necesitar dr, r0, dr_2
dr_2=(double) (r_c *r_c /n);

//Busco los i que se acercan a mi r_2
//esto sale de que *(r+i)**(r+i)=(i+1)*dr_2
/*printf("%d \n",(int) ((r_2 /dr_2)-1));*/
i=(int) ((r_2 /dr_2)-1);

 /*if (i<0) {
 printf("%d \n",i);
 i=0; //parche
 }*/
//La idea es hacer una iteracion lineal para U y F
//Lo hacemos para F
//F(r^2(i+1)) - F(r^2(i))= *(tabla_fz_pot+1+(3*(i+1)))-*( tabla_fz_pot+1+(3*i))
//r(i+1) - r(i) es igual a *(tabla_fz_pot+(3*(i+1)))-*( tabla_fz_pot+(3*i))
m= (*(tabla_fz_pot+1+(3*(i+1)))- *( tabla_fz_pot+1+(3*i))) / dr_2;
b = *( tabla_fz_pot+1+(3*i));
f_nueva=m*(r_2-(i+1)*dr_2)+b;

//Lo hacemos para U
m= (*(tabla_fz_pot+2+(3*(i+1)))- *( tabla_fz_pot+2+(3*i))) / dr_2;
b = *( tabla_fz_pot+2+(3*i));
u_nueva=m*(r_2-(i+1)*dr_2)+b;

/*printf("%lf ",r_2);
printf("%lf ",*(tabla_fz_pot+2+(3*i)));
printf("%lf \n",u_nueva);*/

//f_nueva=*(tabla_fz_pot+1+(3*(i)));
//u_nueva=*(tabla_fz_pot+2+(3*(i)));

//*(tabla_fz_pot+1+(3*(i)))=f_nueva;
//*(tabla_fz_pot+2+(3*(i)))=u_nueva;

*F_mod=f_nueva;




return u_nueva;
}


////////////////////////

double fuerzas (double *x, double *f, float L,  int N,int n,double *tabla_fz_pot, double *p)
{
double U=0;
double r_2;
double deltax,deltay,deltaz;
double F_mod=0;
double r_c=2.5;
*p=(double)N/(L*L*L);
//seteo en 0 las fuerzas
for(int k=0;k<3*N;k++)
{
*(f+k)=0;
}
for (int i =0; i< N; i++){
  double x1= *(x+(3*i)); //Posiciones para la particula i
  double y1= *(x+(3*i)+1);
  double z1= *(x+(3*i)+2);
    for (int j=i+1; j<N; j++){
      double x2= *(x+(3*j));//Posiciones para la particula j
      double y2= *(x+(3*j)+1);
      double z2= *(x+(3*j)+2);
      deltax=delta_x (x1, x2, L);
      deltay=delta_x (y1, y2, L);
      deltaz=delta_x (z1, z2, L);
      /*if (deltax==0){
        printf("%lf ",x2);
        printf("%lf \n",x1);}*/
      r_2=norma_2(deltax,deltay,deltaz);
      /*printf("%lf \n",r_2);*/
    	if( r_2<r_c*r_c)
    	{/*printf("%lf ",r_2);*/
    	U+=interpolar (n, r_2, tabla_fz_pot, & F_mod);

    	*(f+3*i) += deltax*F_mod;
      *(f+(3*i)+1) += deltay*F_mod;
      *(f+(3*i)+2) += deltaz*F_mod;
    	*(f+3*j) -= deltax*F_mod;
      *(f+(3*j)+1) -= deltay*F_mod;
      *(f+(3*j)+2) -= deltaz*F_mod;
	*p+=F_mod*r_2/(3*L*L*L);
    	}
     }
   }
   /*printf("\n");*/
/*printf("Energia pot total por part es %lf \n",U/(double)N);*/
return U;
}

////////////////////////

double presiones (double *x, double *f, float L,  int N,int n, double p,double *tabla_fz_pot)
{
double r_2;
double deltax,deltay,deltaz;
double F_mod=0;
double r_c=2.5;

for(int k=0;k<3*N;k++)
{
*(f+k)=0;
}
for (int i =0; i< N; i++){
  double x1= *(x+3*i); //Posiciones para la particula i
  double y1= *(x+3*i+1);
  double z1= *(x+3*i+2);
    for (int j=i; j<N; j++){
      double x2= *(x+3*j);//Posiciones para la particula j
      double y2= *(x+3*j+1);
      double z2= *(x+3*j+2);
      deltax=delta_x (x1, x2, L);
      deltay=delta_x (y1, y2, L);
      deltaz=delta_x (z1, z2, L);
      r_2=norma_2(deltax,deltay,deltaz);
	    if(r_2<r_c*r_c)
	     {interpolar (n, r_2, tabla_fz_pot, & F_mod);}
       p=F_mod*r_2;
      }
   }
return 0;
}

double rescaling(double *v, double Ttarget,double Tactual,int N)
{
	double lambda=pow(Ttarget/Tactual,1.0/2.0);
	for(int i=0;i<3*N;i++)
	*(v+i)=*(v+i)*lambda;	 
}

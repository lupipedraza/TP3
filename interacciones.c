#include "interacciones.h"
#include <math.h>


//////////////////////////
int armado_tabla (int n ,double *tabla_fz_pot)
{
printf("%i  ", n);
double r_c = 2; //radio de corte
float eps=1.0;
float sigma=1.0;
double F_r;
double U;
double r_2;
double dr_2;

//voy a necesitar dr, r0, dr_2
dr_2=(double)(r_c/n)*r_c;
printf("%f ", dr_2);
for (int i =0; i< n+1; i++){
  r_2=(double)(i+1)*dr_2;
  //printf("%d ", r_2);
  U=4*eps*(2*pow(sigma/r_2,6)-pow(sigma/r_2,3))/sigma;
  F_r=24*eps*(2*pow(sigma/r_2,7)-pow(sigma/r_2,4))/sigma;
  *(tabla_fz_pot+(3*i))=r_2; //guardo el radio
  *(tabla_fz_pot+(1+(3*i)))=F_r; //guardo la fuerza
  *(tabla_fz_pot+(2+(3*i)))=U; //guardo el potencial
  }
//free(tabla_fz_pot) //no se si liberar el malloc, creo que no
return 0;
}
//////////////////////////

double interpolar (double r_2, double *tabla_fz_pot, double *fz_u_nuevas)
{//le paso r_2
//n son los puntos de espaciado en mi espacio para interpolar
int n = 10;
float r_c=2.5;
double dr_2;
int i;
double m;
double b;
double f_nueva;
double u_nueva;

//voy a necesitar dr, r0, dr_2
dr_2=(r_c/n)*r_c;

//Busco los i que se acercan a mi r_2
//esto sale de que *(r+i)**(r+i)=(i+1)*dr_2
i=(int)(r_2  /dr_2)-1;


//La idea es hacer una iteracion lineal para U y F
//Lo hacemos para F
//F(r^2(i+1)) + F(r^2(i))= *(tabla_fz_pot+1+(3*(i+1)))-*( tabla_fz_pot+1+(3*i))
//r(i+1) - r(i) es igual a *(tabla_fz_pot+(3*(i+1)))-*( tabla_fz_pot+(3*i))
m= *(tabla_fz_pot+1+(3*(i+1)))-*( tabla_fz_pot+1+(3*i)) / dr_2;
b = *( tabla_fz_pot+1+(3*i));
f_nueva=m*(r_2-(i+1)*dr_2)+b;
//Lo hacemos para U
m= *(tabla_fz_pot+2+(3*(i+1)))-*( tabla_fz_pot+2+(3*i)) / dr_2;
b = *( tabla_fz_pot+2+(3*i));
u_nueva=m*(r_2-(i+1)*dr_2)+b;

*(fz_u_nuevas)=f_nueva;
*(fz_u_nuevas+1)=u_nueva;

return 0;
}

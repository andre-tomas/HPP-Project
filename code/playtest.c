#include<stdio.h>
#include<stdlib.h>
#include<math.h>


const double PI = 3.14159265359;
const double e = 2.718281828459;





int main() {

  double X = 1;
  double T = 1;

  double dx = 0.1;
  double dt = 0.001;
  double r = dt/(dx*dx);

  int Nx = X/dx;
  int Nt = T/dt;


  double* U = (double*)malloc(Nx*sizeof(double));

  double temp1;
  double x;
  for (int i = 0; i <= Nx; i++) {
    x = (double)i*dx;
    temp1 = 10000000000*sin(5*PI*x)/(PI*PI);
    U[i] = temp1;
  }
  

  printf("r = %f\n",r);
  
  double* Uold = (double*)malloc(Nx*sizeof(double));

  
  for (int i = 1; i <= Nt; i++) {
    Uold = U;
    for (int j = 1; j < Nx; j++) {
      
      U[j] = Uold[j] + r*(Uold[j-1] - 2*Uold[j] + Uold[j+1]);
    }
    U[0] = 0;
    U[Nx] = 0;
  }

  
  for (int i = 0; i <= Nx; i++) {
    printf("U(%f,1) = %f\n",(double)i*dx,U[i]);
  }

  printf("True solution U(0.5,1) = %f\n",sin(PI/2)/(PI*PI*e));
  

  
}


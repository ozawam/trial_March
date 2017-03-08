//time change of isothermal uniformsphere
//gnuplot
#include  <fstream>
#include  <assert.h>
#include  <math.h>
#include  <iostream>
#include  <cstdlib>
using namespace std;

#include <stdio.h>
#include <stdlib.h>

#define NMAX 16384
#define SQR(x) ((x)*(x))

#define G 1.0
#define M 1.0
#define R 1.0

void calc_force(int n, double m[], double x[][3], double a[][3], double eps2,double W);

void leap_frog(
int n, double m[], double x[][3], double v[][3], double a[][3],
double dt, double eps2,double W,double K)
{
  int i,k;
  double vhalf[NMAX][3];
  double V2;
  //v0.5
  for(i=0;i<n;i++){
    for(k=0;k<3;k++){
      vhalf[i][k]=v[i][k]+a[i][k]*dt*0.5;
    }
  }
  //x1
  for(i=0;i<n;i++){
    for(k=0;k<3;k++){
      x[i][k] += vhalf[i][k]*dt;
    }
  }

  //a1
  calc_force(n, m, x, a, eps2,W);

  //v1,K
  K=0.0;
  for(i=0;i<n;i++){
    for(k=0;k<3;k++){
      v[i][k]=vhalf[i][k]+a[i][k]*dt*0.5;
    }

      V2=pow(v[i][1],2.0)+pow(v[i][2],2.0)+pow(v[i][1],2.0);
      K+=0.5*m[i]*V2;

  }


}

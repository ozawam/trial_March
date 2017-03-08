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

void calc_force(int n, double m[], double x[][3], double a[][3], double eps2,double W)
{
  int i,j,k;
  double r[3],r3inv,rij;
  W=0.0;
  for(i=0;i<n;i++){
    for(k=0;k<3;k++){
      a[i][k] = 0.0;
    }
  }

  for(i=0;i<n-1;i++){
    for(j=i+1;j<n;j++){
      r[0]=x[j][0]-x[i][0];
      r[1]=x[j][1]-x[i][1];
      r[2]=x[j][2]-x[i][2];
      r3inv=1.0/pow(sqrt(pow(r[0],2.0)+pow(r[1],2.0)+pow(r[2],2.0)+eps2),3.0);

      rij=sqrt(pow(x[i][0]-x[j][0],2.0)+pow(x[i][1]-x[j][1],2.0)+pow(x[i][2]-x[j][2],2.0));
      W -= (m[i]*m[j])/sqrt(pow(rij,2.0)+eps2);

      for(k=0;k<3;k++){
	a[i][k] += m[j]*r[k]*r3inv;
	a[j][k] += -m[i]*r[k]*r3inv;
      }
    }
  }
}

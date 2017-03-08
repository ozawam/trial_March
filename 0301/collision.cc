//collision of arp271
//energy
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

void leap_frog(int n, double m[], double x[][3], double v[][3], double a[][3],
	       double dt, double eps2,double W,double K);

int main(void)
{
  int i,j,k;
  // number of particles
  int n;
  //dimension
  int dim;
  // particle data
  static double m[NMAX], x[NMAX][3], v[NMAX][3], a[NMAX][3];
  // system energy, Virial ratio
  // double e, e_ini, r_v;
  double  r_v;
  //time, timestep, end time, data interval
  double t, dt, t_end;
  // squared softening parameter
  double eps2;
  // setting simulation parameters
  double W,K,E;
  //energy

  r_v=0.1;
  eps2=pow(0.03125,2.0);

  cout <<"dt = ";cin >> dt;
  cout <<"t_end = ";cin >> t_end;








  //Manual variable start

  /* initialization of particle data */
  /*K0,W0 */
  double K0,W0;
  FILE *fp;
  fp = fopen("arp271.ascii","r");
  fscanf(fp,"%d%d%lf",&n,&dim,&t);
  for(i=0;i<n;i++) fscanf(fp,"%lf",&m[i]);
  for(i=0;i<n;i++) fscanf(fp,"%lf%lf%lf",&x[i][0],&x[i][1],&x[i][2]);
  for(i=0;i<n;i++) fscanf(fp,"%lf%lf%lf",&v[i][0],&v[i][1],&v[i][2]);
  fclose(fp);

  cout << "dt=" << dt << endl ;
 
  /* preparation for output */
  int Nt,interval; //Nt:Number of trials
  Nt=0;
  interval=10;

  ofstream disk_right("arp271_right_nobh.dat"),disk_left("arp271_left_nobh.dat"),energy_all("arp271_energy_all_nobh.dat");


  //Manual variable end



  cout << "dt=" << dt << endl ;

  W0=0.0;
  K0=0.0;
  double r0ij;
  double V20;
  for(i=0;i<n-1;i++){
    for(j=i+1;j<n;j++){
      r0ij=sqrt(pow(x[i][0]-x[j][0],2.0)+pow(x[i][1]-x[j][1],2.0)+pow(x[i][2]-x[j][2],2.0));
      W0 -= (m[i]*m[j])/sqrt(pow(r0ij,2.0)+eps2);
   }

  }
 for(i=0;i<n;i++){
  V20=pow(v[i][0],2.0)+pow(v[i][1],2.0)+pow(v[i][2],2.0);
    K0+=0.5*m[i]*V20;
 }

 W=W0;
 K=K0;
 E=W+K;
  /* a0 */
 calc_force(n, m, x, a, eps2,W);


  /*initial condition*/
  for ( i=0 ; i<n/2; i++ ){
    disk_right<< x[i][0] <<" "<< x[i][1] <<" "<< x[i][2]  << endl;
  }
  disk_right<< " "<< endl  << endl;
  for ( i=n/2 ; i<n; i++ ){
    disk_left<< x[i][0] <<" "<< x[i][1] <<" "<< x[i][2]  << endl;
  }
  disk_left<< " "<< endl  << endl;


  energy_all<< 0.0 <<" "<< E  << endl;
  energy_all<< " "<< endl  << endl;


  /*calculation */
  while(t<t_end){

    /* time integration */
    leap_frog(n, m, x, v, a, dt, eps2,W,K);
    E=W+K;
    /*output*/
    if (Nt%interval == 0 ){
      for ( i=0 ; i<n/2; i++ ){
	disk_right<< x[i][0] <<" "<< x[i][1] <<" "<< x[i][2]  << endl;
      }
      disk_right<< " "<< endl  << endl;
      for ( i=n/2 ; i<n; i++ ){
	disk_left<< x[i][0] <<" "<< x[i][1] <<" "<< x[i][2]  << endl;
      }
      disk_left<< " "<< endl  << endl;

      energy_all<< t <<" "<< E  << endl;
      energy_all<< " "<< endl  << endl;

    }
    t += dt;
    Nt +=1;
  }



  /* integration error check */

  double relative_error,dE,Eend,E0;
  double Kend,Wend;

  double V2end;
  double rij;
    Kend=0.0;
    Wend=0.0;
    for(i=0;i<n-1;i++){
      for(j=i+1;j<n;j++){
	rij=sqrt(pow(x[i][0]-x[j][0],2.0)+pow(x[i][1]-x[j][1],2.0)+pow(x[i][2]-x[j][2],2.0));
	Wend -= (m[i]*m[j])/sqrt(pow(rij,2.0)+eps2);
      }
    }
    for(i=0;i<n;i++){
      V2end=pow(v[i][0],2.0)+pow(v[i][1],2.0)+pow(v[i][2],2.0);
      Kend +=0.5*m[i]*V2end;
    }

  E0=K0+W0;
  Eend=Kend+Wend;
  dE=Eend-E0;
  relative_error=fabs(dE/E0);

  //  fprintf(stderr,"K0 = %g\n",K0);
  //  fprintf(stderr,"W0 = %g\n",W0);
  //  fprintf(stderr,"E0 = %g\n",E0);
  //  fprintf(stderr,"Kend = %g\n",Kend);
  //  fprintf(stderr,"Wend = %g\n",Wend);
  //  fprintf(stderr,"Eend = %g\n",Eend);
  //  fprintf(stderr,"dE = %g\n",dE);

  cout << "relative_error =" << relative_error << endl;
  cout << "dt=" << dt << endl ;

  //  fprintf(stderr,"relative_error = %g\n",relative_error);
  //  fprintf(stderr,"dt = %g\n",dt);
  return(0);
}

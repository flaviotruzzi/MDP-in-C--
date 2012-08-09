/*
 * Simulator.cpp
 *
 *  Created on: Jul 30, 2012
 *      Author: ftruzzi
 */
#include <iostream>
#include <cstdlib>
#include "Simulator.h"
#include <random>

using namespace Eigen;
using namespace std;

Simulator::Simulator(int C, int G, int B, MatrixXd CTR, MatrixXd CPC, int tau, int sims, double Prequest, double *Pg, MDP *mdp) {

  n_means = sims;

  cout << "Creating Simulation Matrix...";
  srand((unsigned)time(0));

  this->mdp = mdp;
  this->Pg = new double[G];
  this->tau = tau;
  this->C = C;
  this->G = G;
  this->B = B;
  this->Prequest = Prequest;
  this->CPC = CPC;
  distribution = bernoulli_distribution(Prequest);
  for (int i = 0; i < G; i++)
    this->Pg[i] = Pg[i];

  for (int i = 1; i < G; i++) {
	  this->Pg[i] = this->Pg[i] + this->Pg[i-1];
  }

 simulations = new MatrixXi[sims];

 this->CTR = CTR;

 for (int r = 0; r < sims; r++) {
     simulations[r] = MatrixXi(C+1,tau);
     for (int t = 0; t < tau; t++) {
       int g = randomWeighted();
       if (g > 0) {
         for (int c = 0; c < C; c++) {
           double rnd = double(rand())/RAND_MAX;
           if (rnd < CTR(g-1,c))
             simulations[r](c,t) = 1;
           else
             simulations[r](c,t) = 0;
         }
       }
       simulations[r](C,t) = g;
     }
   }
 cout << "Done!" << endl;
}

int Simulator::randomWeighted() {

  double rnd = double(rand())/RAND_MAX;
  if (distribution(generator) == true) {
      for (int i = 0; i < G; i++) {
          if (rnd < Pg[i])
            return i+1;
      }
  }
  return 0;
}


void printState(int *s, int C) {
	cout << "[";
	for (int i = 0; i < C+1; i++)
		cout << s[i] << " ";
	cout << "]";
}

void Simulator::Simulate() {
	cout << "Simulating...";
	values = MatrixXd(n_means,tau);
	values.setConstant(0.0);
	for (int r = 0; r < n_means; r++) {
		int s[C+1];
		for (int si = 0; si < C; si++)
			s[si] = B;
		s[C] = 0;
		for (int t = 0; t < tau; t++) {
			int g = simulations[r](C,t); // teve requisição!?
			s[C] = g;
			int c = mdp->getAction(mdp->getIndexOfState(s),t);
			if ((g>0) && (c>0) && (s[c-1] > 0) && (simulations[r](c-1,t) > 0)) {
				values(r,t) = simulations[r](c-1,t)*CPC(c-1);
				cout << "t: " << t << " "; printState(s,C);
				cout << " " << "index:" << mdp->getIndexOfState(s) << " ação:" << c << endl;
				s[c-1] = s[c-1] -1;
			}
		}
	}
	cout << "Done!" << endl;
}

Simulator::~Simulator()
{
  // TODO Auto-generated destructor stub
}


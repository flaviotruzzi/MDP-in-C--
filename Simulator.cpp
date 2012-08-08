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
  srand((unsigned)time(NULL));

  this->mdp = mdp;
  this->Pg = new double[G];
  this->tau = tau;
  this->C = C;
  this->G = G;
  this->B = B;
  this->Prequest = Prequest;
  this->CPC = CPC;

  for (int i = 0; i < 3; i++)
    this->Pg[i] = Pg[i];

 simulations = new MatrixXd[sims];

 this->CTR = CTR;

 for (int r = 0; r < sims; r++) {
     simulations[r] = MatrixXd(C+1,tau);
     for (int t = 0; t < tau; t++) {
       int g = randomWeighted();
       if (! ((double(rand())/RAND_MAX) < Prequest))
         g = 0;
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

  default_random_engine generator;
  bernoulli_distribution distribution(Prequest);
  double rnd = double(rand())/RAND_MAX;
  if (distribution(generator)) {
      for (int i = 0; i < 3; i++) {
          if (rnd < Pg[i])
            return i+1;
      }
  }
  return 0;
}


void Simulator::Simulate() {
	cout << "Simulating...";
	values = MatrixXd(n_means,tau);
	for (int r = 0; r < n_means; r++) {
		int s[C+1];
		for (int si = 0; si < C; si++)
			s[si] = B;
		s[C] = 0;
		for (int t = 0; t < tau; t++) {
			int g = simulations[r](C,t);
			int c = mdp->getAction(mdp->getIndexOfState(s),t);
			if ((g > 0) && (c > 0) && (simulations[r](c,t) > 0) && (s[c] > 0)) {
				s[c] = s[c] -1;
				values(r,t) = simulations[r](c,t)*CPC(c);
			}
		}
	}
	cout << "Done!" << endl;
}

Simulator::~Simulator()
{
  // TODO Auto-generated destructor stub
}


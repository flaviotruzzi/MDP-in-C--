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

using namespace std;

Simulator::Simulator(int C, int G, MatrixXf CTR, int tau, int sims, double Prequest, double *Pg) {

  n_means = sims;

  cout << "Creating Simulation Matrix...";
  srand((unsigned)time(NULL));

  this->Pg = new double[G];

  this->Prequest = Prequest;

  for (int i = 0; i < 3; i++)
    this->Pg[i] = Pg[i];

 simulations = new MatrixXf[sims];

 this->CTR = CTR;

 for (int r = 0; r < sims; r++) {
     simulations[r] = MatrixXf(C+1,tau);
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

  std::default_random_engine generator;
  std::bernoulli_distribution distribution(Prequest);
  double rnd = double(rand())/RAND_MAX;
  if (distribution(generator)) {
      for (int i = 0; i < 3; i++) {
          if (rnd < Pg[i])
            return i+1;
      }
  }
  return 0;
}


Simulator::~Simulator()
{
  // TODO Auto-generated destructor stub
}


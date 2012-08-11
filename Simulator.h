/*
 * Simulator.h
 *
 *  Created on: Jul 30, 2012
 *      Author: ftruzzi
 */

#ifndef SIMULATOR_H_
#define SIMULATOR_H_

#include <Eigen/Dense>
#include "MDP.h"
#include <random>

using namespace Eigen;
using namespace std;



class Simulator
{
public:
  Simulator(int C, int G, int B, MatrixXld CTR, MatrixXld CPC, int tau, int sims, MYTYPE Prequest, MYTYPE *Pg, MDP *mdp);
  int randomWeighted();
  MatrixXi *simulations;
  virtual  ~Simulator();
  int n_means;
  void Simulate();
  MatrixXld values;
private:
  MYTYPE *Pg;
  MYTYPE Prequest;
  int tau;
  int C;
  MatrixXld CTR;
  MatrixXld CPC;
  default_random_engine generator;
  bernoulli_distribution distribution;
  MDP *mdp;
  int B;
  int G;



};

#endif /* SIMULATOR_H_ */

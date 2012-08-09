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
  Simulator(int C, int G, int B, MatrixXd CTR, MatrixXd CPC, int tau, int sims, double Prequest, double *Pg, MDP *mdp);
  int randomWeighted();
  MatrixXi *simulations;
  virtual  ~Simulator();
  int n_means;
  void Simulate();
  MatrixXd values;
private:
  double *Pg;
  double Prequest;
  int tau;
  int C;
  MatrixXd CTR;
  MatrixXd CPC;
  default_random_engine generator;
  bernoulli_distribution distribution;
  MDP *mdp;
  int B;
  int G;



};

#endif /* SIMULATOR_H_ */

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

using namespace Eigen;

class Simulator
{
public:
  Simulator(int C, int G, int B, MatrixXd CTR, MatrixXd CPC, int tau, int sims, double Prequest, double *Pg, MDP *mdp);
  int randomWeighted();
  MatrixXd *simulations;
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

  MDP *mdp;
  int B;
  int G;



};

#endif /* SIMULATOR_H_ */

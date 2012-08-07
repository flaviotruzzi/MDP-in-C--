/*
 * Simulator.h
 *
 *  Created on: Jul 30, 2012
 *      Author: ftruzzi
 */

#ifndef SIMULATOR_H_
#define SIMULATOR_H_

#include <Eigen/Dense>

using namespace Eigen;

class Simulator
{
public:
  Simulator(int C, int G, MatrixXf CTR, int tau, int sims, double Prequest, double *Pg);
  int randomWeighted();
  MatrixXf *simulations;
  virtual
  ~Simulator();
  int n_means;

private:
  double *Pg;
  double Prequest;
  MatrixXf CTR;


};

#endif /* SIMULATOR_H_ */

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
  Simulator(int C, int G, int tau, int sims, double Prequest, double *Pg);
  int randomWeighted();
  MatrixXd *simulations;
  virtual
  ~Simulator();

private:
  double *Pg;
  double Prequest;
  Matrix3d CTR;

};

#endif /* SIMULATOR_H_ */

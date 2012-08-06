/*
 * MDP.h
 *
 *  Created on: Jul 30, 2012
 *      Author: ftruzzi
 */

#ifndef MDP_H_
#define MDP_H_
#define EIGEN_YES_I_KNOW_SPARSE_MODULE_IS_NOT_STABLE_YET
#include <Eigen/Dense>
#include <Eigen/Sparse>
#include "Simulator.h"

using namespace Eigen;

class MDP
{
public:
  MDP(int C, int G, int B, int tau, double Prequest, MatrixXf CTR, double Pg[], VectorXf CPC);
  void getStateOfIndex(long index, int *s);
  void PopulateMtx();
  void plan();
  int getIndexOfState(int *s);
  int checkT();

  virtual
  ~MDP();

private:
  int C;
  int G;
  long S;
  int A;
  int B;
  int tau;
  MatrixXf eCPI;
  MatrixXf CTR;
  double *Pg;
  VectorXf CPC;
  VectorXf V;
  MatrixXf Q;
  MatrixXf policy;
  SparseMatrix<double> *T;
  SparseVector<double> *R;
  double Prequest;
};

#endif /* MDP_H_ */

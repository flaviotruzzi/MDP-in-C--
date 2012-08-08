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


using namespace Eigen;

class MDP
{
public:
  MDP(int C, int G, int B, int tau, double Prequest, MatrixXd CTR, double *Pg, VectorXd CPC);
  void getStateOfIndex(long index, int *s);
  void PopulateMtx();
  void ValueIteration();
  int getIndexOfState(int *s);
  int getAction(long index, int t);
  int checkT();
  MatrixXi policy;
  SparseMatrix<double> *T;
  virtual
  ~MDP();

private:
  int C;
  int G;
  long S;
  int A;
  int B;
  int tau;
  MatrixXd eCPI;
  MatrixXd CTR;
  double *Pg;
  VectorXd CPC;
  MatrixXd V;
  MatrixXd Q;
  //SparseMatrix<double> *T;
  SparseMatrix<double> *R;
  double Prequest;
};

#endif /* MDP_H_ */

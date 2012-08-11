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

typedef double MYTYPE;

typedef Matrix<MYTYPE, Dynamic, Dynamic> MatrixXld;
typedef Matrix<MYTYPE, Dynamic, 1> VectorXld;

class MDP
{
public:
  MDP(int C, int G, int B, int tau, MYTYPE Prequest, MatrixXld CTR, MYTYPE *Pg, VectorXld CPC);
  void getStateOfIndex(long index, int *s);
  void PopulateMtx();
  void ValueIteration();
  int getIndexOfState(int *s);
  int getAction(long index, int t);
  int checkT();
  MatrixXi policy;
  SparseMatrix<MYTYPE> *T;
  MatrixXld *R;
  MatrixXld V;
  MatrixXld eCPI;
  virtual
  ~MDP();

private:
  int C;
  int G;
  long S;
  int A;
  int B;
  int tau;

  MatrixXld CTR;
  MYTYPE *Pg;
  VectorXld CPC;

  MatrixXld Q;
  //SparseMatrix<double> *T;
//  SparseMatrix<double> *R;
  MYTYPE Prequest;
};

#endif /* MDP_H_ */

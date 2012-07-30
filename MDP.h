/*
 * MDP.h
 *
 *  Created on: Jul 30, 2012
 *      Author: ftruzzi
 */

#ifndef MDP_H_
#define MDP_H_

#include <Eigen/Dense>
#include <Eigen/Sparse>

using namespace Eigen;

class MDP
{
public:
  MDP(int C, int G, int B, double Prequest, MatrixXf CTR, double Pg[], MatrixXf CPC);
  void getStateOfIndex(long index, int **s);
  int getIndexOfState(int *s);

  virtual
  ~MDP();

private:
  int C;
  int G;
  long S;
  int A;
  int B;
  MatrixXf eCPI;
  MatrixXf CTR;
  double *Pg;
  MatrixXf CPC;
  SparseMatrix<double> *T;
  SparseVector<double> *R;
  double Prequest;
};

#endif /* MDP_H_ */

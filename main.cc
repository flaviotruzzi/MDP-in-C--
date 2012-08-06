/*
 * main.cc
 *
 *  Created on: Jul 30, 2012
 *      Author: ftruzzi
 */

#define EIGEN_YES_I_KNOW_SPARSE_MODULE_IS_NOT_STABLE_YET

#include <iostream>
#include "Simulator.h"
#include <Eigen/Dense>
#include "MDP.h"

using namespace std;
using namespace Eigen;

int main(int argc, char **argv) {

  double Pg[] = { 0.4, 0.1, 0.25, 0.25};

  //Simulator a(3,3,500,1000,.4,Pg);

  MatrixXf CTR(3,4);
  CTR << 0.05, 0.50, 0.05, .1,
         0.80, 0.81, 0.05, .4,
         0.05, 0.81, 0.80, .7;

  VectorXf CPC(4);

  CPC << 1.0, 1.0, 1.0, 1.0;

  MDP k(4,3,10,.4,CTR,Pg,CPC);

  k.PopulateMtx();
  //k.checkT();

  return 0;
}


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

  double Pg[] = { 0.3, 0.1, 0.1, 0.25, 0.25};

  //Simulator a(3,3,500,1000,.4,Pg);

  MatrixXf CTR(3,5);
  CTR << 0.05, 0.50, 0.05, .1, .45,
         0.80, 0.81, 0.05, .4, .65,
         0.05, 0.81, 0.80, .7, .44;

  VectorXf CPC(5);

  CPC << 1.0, 1.0, 1.0, 1.0, 1.0;

  MDP k(5,3,15,.4,CTR,Pg,CPC);

  k.PopulateMtx();
  //k.checkT();

  return 0;
}


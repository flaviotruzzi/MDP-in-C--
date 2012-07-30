/*
 * main.cc
 *
 *  Created on: Jul 30, 2012
 *      Author: ftruzzi
 */

#include <iostream>
#include "Simulator.h"

using namespace std;

int main(int argc, char **argv) {

  double Pg[] = { 0.5, 0.75, 1.0};

  Simulator a(3,3,500,1000,.4,Pg);


  int k1=0;
  int k2=0;
  int k3=0;

  for (int i = 0; i < 1000; i++) {
      k1 += ((MatrixXd) a.simulations[i]).row(0).sum();
      k2 += ((MatrixXd) a.simulations[i]).row(1).sum();
      k3 += ((MatrixXd) a.simulations[i]).row(2).sum();
  }

  cout << k1/1000. << endl;
  cout << k2/1000. << endl;
  cout << k3/1000. << endl;

  return 0;
}


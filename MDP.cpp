/*
 * MDP.cpp
 *
 *  Created on: Jul 30, 2012
 *      Author: ftruzzi
 */

#include "MDP.h"

#include <math.h>
#include <Eigen/Array>

MDP::MDP(int C, int G, int B, double Prequest, MatrixXf CTR, double Pg[], MatrixXf CPC)
{
  this->C =  C;
  this->G =  G;
  this->B =  B;
  this->Prequest = Prequest;

  this->CTR = CTR;

  this->Pg = new double[G];

  for (int i = 0; i < G; i++)
    this->Pg[i] = Pg[i];

  this->CPC = CPC;

  S = pow((B+1),C)*(C+1);
  A = C+1;

  T = new SparseMatrix<double>[A];
  R = new SparseVector<double>[A];

  int *sa =  new int[C+1];
  int *sc =  new int[C+1];



  for (int a = 0; a < A; a++) {
      T[a] = SparseMatrix<double>(S,S);
      R[a] = SparseVector<double>(S);
      for (int s = 0; s < S; s++) {
          getStateOfIndex(s,&sa);

          for (int g = 0; g < G; g++) {
              memcpy(sc,sa,sizeof(sa));

              sc[C] = g;

              float PI = 0;

              if (sc[C] == 0)
                PI =  1-Prequest;
              else
                PI = Prequest*Pg[sc[C]];

              if ((a > 0) && (sa[C] > 0) && (sa[a] > 0)) {
                  T[a](s,getIndexOfState(sc)) = PI*(1-CTR(sa[C],a-1));
                  sc[a] = sc[a]-1;
                  T[a](s,getIndexOfState(sc)) = PI*CTR(sa[C],a-1);
                  R[a](s) = eCPI(sa[C],a-1);
              } else {
                  T[a](s,getIndexOfState(sc)) = PI;
              }

          }

      }
  }

  delete sa;
  delete sc;

}

int MDP::getIndexOfState(int *s) {
  return 0;
}

void MDP::getStateOfIndex(long index, int **s) {

  return;

}

MDP::~MDP()
{
  // TODO Auto-generated destructor stub
}


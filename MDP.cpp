/*
 * MDP.cpp
 *
 *  Created on: Jul 30, 2012
 *      Author: ftruzzi
 */
#define EIGEN_YES_I_KNOW_SPARSE_MODULE_IS_NOT_STABLE_YET
#include "MDP.h"

#include <math.h>
#include <iostream>

using namespace std;

typedef Eigen::Triplet<double> Tr;

void print(int *v) {
  cout << "[" << v[0] << " " << v[1] << " " << v[2] << " "<< v[3] << "]" << endl;
}

MDP::MDP(int C, int G, int B, int tau, double Prequest, MatrixXd CTR, double Pg[], VectorXd CPC)
{
  this->C =  C;
  this->G =  G;
  this->B =  B;
  this->tau = tau;
  this->Prequest = Prequest;

  this->CTR = CTR;

  this->Pg = new double[G];

  for (int i = 0; i < G; i++)
    this->Pg[i] = Pg[i];

  this->CPC = CPC;

  S = (long)(pow(int(B+1),double(C))*(G+1));
  A = C+1;

  T = new SparseMatrix<double>[A];
  R = new SparseMatrix<double>[A];

  eCPI = CTR.cwiseProduct(CPC.transpose().replicate(G,1));

}

void MDP::PopulateMtx() {

  int *sa =  new int[C+1];
  int *sc =  new int[C+1];

  cout << "Creating Transation and Reward Matrices... ";

  for (int a = 0; a < A; a++) {
      T[a] = SparseMatrix<double>(S,S);
      R[a] = SparseMatrix<double>(S,1);


      R[a].reserve(600000);

      int nonzero = 0;
      std::vector<Tr> K;
      std::vector<Tr> Kr;
      K.reserve(600000);
      Kr.reserve(600000);

      for (int s = 0; s < S; s++) {
          getStateOfIndex(s,sa);

          for (int g = 0; g < G+1; g++) {

              memcpy(sc,sa,C*sizeof(int));

              sc[C] = g;

              float PI = 0;

              if (g == 0)
                PI =  1-Prequest;
              else
                PI = Prequest*Pg[g-1];

              if ( (a != 0) && (sa[C] > 0) && (sa[a-1] > 0)) {

            	  K.push_back(Tr(s,getIndexOfState(sc),PI*(1-CTR(sa[C]-1,a-1))));

                  sc[a-1] = sc[a-1]-1;

                  K.push_back(Tr(s,getIndexOfState(sc),PI*CTR(sa[C]-1,a-1)));

                  Kr.push_back(Tr(s,0,eCPI(sa[C]-1,a-1)));

                  nonzero = nonzero +2;
              } else {
                  nonzero++;

                  K.push_back(Tr(s,getIndexOfState(sc),PI));
              }

          }
      }

      T[a].setFromTriplets(K.begin(),K.end());
      R[a].setFromTriplets(Kr.begin(),Kr.end());
      R[a].finalize();
      T[a].finalize();

      //cout << "a:" << a << " " << nonzero << endl;
  }
  cout << "Done!" << endl;
  delete sa;
  delete sc;

}

int MDP::checkT() {
  int result = 0;

  cout << T[1].coeff(5307,4821)<< "    0.0100"<< endl;
  cout << T[1].coeff(4820,4822)<< "    0.1000"<< endl;
  cout << T[1].coeff(4821,4822)<< "    0.0950"<< endl;
  cout << T[1].coeff(4822,4822)<< "    0.0200"<< endl;
  cout << T[1].coeff(4823,4822)<< "    0.0950"<< endl;
  cout << T[1].coeff(5305,4822)<< "    0.0050"<< endl;
  cout << T[1].coeff(5306,4822)<< "    0.0800"<< endl;
  cout << T[1].coeff(5307,4822)<< "    0.0050"<< endl;
  cout << T[1].coeff(4820,4823)<< "    0.1000"<< endl;
  cout << T[1].coeff(4821,4823)<< "    0.0950"<< endl;
  cout << T[1].coeff(4822,4823)<< "    0.0200"<< endl;
  cout << T[1].coeff(4823,4823)<< "    0.0950"<< endl;
  cout << T[1].coeff(5305,4823)<< "    0.0050"<< endl;
  cout << T[1].coeff(5306,4823)<< "    0.0800"<< endl;
  cout << T[1].coeff(5307,4823)<< "    0.0050"<< endl;
  cout << T[1].coeff(4824,4824)<< "    0.6000"<< endl;
  cout << T[1].coeff(4825,4824)<< "    0.5700"<< endl;
  cout << T[1].coeff(4826,4824)<< "    0.1200"<< endl;
  cout << T[1].coeff(4827,4824)<< "    0.5700"<< endl;
  cout << T[1].coeff(5309,4824)<< "    0.0300"<< endl;
  cout << T[1].coeff(5310,4824)<< "    0.4800"<< endl;
  cout << T[1].coeff(5311,4824)<< "    0.0300"<< endl;
  cout << T[1].coeff(4824,4825)<< "    0.2000"<< endl;
  cout << T[1].coeff(4825,4825)<< "    0.1900"<< endl;
  cout << T[1].coeff(4826,4825)<< "    0.0400"<< endl;
  cout << T[1].coeff(4827,4825)<< "    0.1900"<< endl;
  cout << T[1].coeff(5309,4825)<< "    0.0100"<< endl;
  cout << T[1].coeff(5310,4825)<< "    0.1600"<< endl;
  cout << T[1].coeff(5311,4825)<< "    0.0100"<< endl;
  cout << T[1].coeff(4824,4826)<< "    0.1000"<< endl;
  cout << T[1].coeff(4825,4826)<< "    0.0950"<< endl;
  cout << T[1].coeff(4826,4826)<< "    0.0200"<< endl;
  cout << T[1].coeff(4827,4826)<< "    0.0950"<< endl;
  cout << T[1].coeff(5309,4826)<< "    0.0050"<< endl;
  cout << T[1].coeff(5310,4826)<< "    0.0800"<< endl;
  cout << T[1].coeff(5311,4826)<< "    0.0050"<< endl;
  cout << T[1].coeff(4824,4827)<< "    0.1000"<< endl;

  cout << T[1].coeff(5318,5316)<< "    0.1200"<< endl;
  cout << T[1].coeff(5319,5316)<< "    0.5700"<< endl;
  cout << T[1].coeff(5316,5317)<< "    0.2000"<< endl;
  cout << T[1].coeff(5317,5317)<< "    0.1900"<< endl;
  cout << T[1].coeff(5318,5317)<< "    0.0400"<< endl;
  cout << T[1].coeff(5319,5317)<< "    0.1900"<< endl;
  cout << T[1].coeff(5316,5318)<< "    0.1000"<< endl;
  cout << T[1].coeff(5317,5318)<< "    0.0950"<< endl;
  cout << T[1].coeff(5318,5318)<< "    0.0200"<< endl;
  cout << T[1].coeff(5319,5318)<< "    0.0950"<< endl;
  cout << T[1].coeff(5316,5319)<< "    0.1000"<< endl;
  cout << T[1].coeff(5317,5319)<< "    0.0950"<< endl;
  cout << T[1].coeff(5318,5319)<< "    0.0200"<< endl;
  cout << T[1].coeff(5319,5319)<< "    0.0950"<< endl;
  cout << T[1].coeff(5320,5320)<< "    0.6000"<< endl;
  cout << T[1].coeff(5321,5320)<< "    0.5700"<< endl;
  cout << T[1].coeff(5322,5320)<< "    0.1200"<< endl;
  cout << T[1].coeff(5323,5320)<< "    0.5700"<< endl;
  cout << T[1].coeff(5320,5321)<< "    0.2000"<< endl;
  cout << T[1].coeff(5321,5321)<< "    0.1900"<< endl;
  cout << T[1].coeff(5322,5321)<< "    0.0400"<< endl;
  cout << T[1].coeff(5323,5321)<< "    0.1900"<< endl;
  cout << T[1].coeff(5320,5322)<< "    0.1000"<< endl;
  cout << T[1].coeff(5321,5322)<< "    0.0950"<< endl;
  cout << T[1].coeff(5322,5322)<< "    0.0200"<< endl;
  cout << T[1].coeff(5323,5322)<< "    0.0950"<< endl;
  cout << T[1].coeff(5320,5323)<< "    0.1000"<< endl;
  cout << T[1].coeff(5321,5323)<< "    0.0950"<< endl;
  cout << T[1].coeff(5322,5323)<< "    0.0200"<< endl;
  cout << T[1].coeff(5323,5323)<< "    0.0950"<< endl;


  return result;
}

int MDP::getIndexOfState(int *s) {
  int n = C-1;
  int p = 0;
  for (int i = 0; i < C; i++) {
      p = p + s[i]*pow(int(B+1),double(n));
      n = n -1;
  }
  p = p*(G+1) + s[C];

  return p;
}

void MDP::getStateOfIndex(long index, int *s) {

  s[C] = index%(G+1);
  index = index/(G+1);

  for (int i = C-1; i != -1; i--) {
      s[i] = index%(B+1);
      index = index/(B+1);
  }

}

void MDP::ValueIteration() {
   cout << "Running Value Iteration	";
   cout.flush();
   V = MatrixXd(S,1);
   V.setConstant(0.0);
   policy = MatrixXi(S,tau);
   Q = MatrixXd(S,A);
   Q.setConstant(0.0);
   	   int counter = 0;
   for (int t = 0; t < tau; t++) {
      for (int a = 0; a < A; a++) {
         Q.col(a) = T[a]*V;
         Q.col(a) += R[a];
      }
      V = Q.rowwise().maxCoeff();
      for (int s = 0; s < S; s++) {
    	  int k;
    	  Q.row(s).maxCoeff(&k);
    	  policy(s,t) = k;
      }
      if (t/100 == counter) {
    	  counter++;
    	  cout << ".";
    	  cout.flush();
      }
   }
   cout << "Done" << endl;
}

int MDP::getAction(long index, int t) {
	return policy(index,t);
}


MDP::~MDP()
{
  // TODO Auto-generated destructor stub
}

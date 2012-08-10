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
typedef std::pair<unsigned long, unsigned long> MyTr;


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
  R = new MatrixXd[A];

  eCPI = CTR.cwiseProduct(CPC.transpose().replicate(G,1));

}

void MDP::PopulateMtx() {

  int *sa =  new int[C+1];
  int *sc =  new int[C+1];

  cout << "Creating Transation and Reward Matrices... ";

  for (int a = 0; a < A; a++) {
      T[a] = SparseMatrix<double>(S,S);
      R[a] = MatrixXd(S,1);


      int nonzero = 0;
      int refused = 0;
      std::vector<Tr> K;
      std::map<MyTr, bool> Kmap;

      K.reserve(600000);

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

            	  if ( Kmap.find(MyTr(s,getIndexOfState(sc))) == Kmap.end()) {
            		  K.push_back(Tr(s,getIndexOfState(sc),PI*(1-CTR((sa[C]-1),a-1))));
            		  Kmap[MyTr(s,getIndexOfState(sc))] = true;
            		  R[a].coeffRef(s,0) = eCPI(sa[C]-1,a-1);
                      nonzero = nonzero +2;
            	  } else {
            		  refused++;
            	  }

                  sc[a-1] = sc[a-1]-1;

            	  if ( Kmap.find(MyTr(s,getIndexOfState(sc))) == Kmap.end()) {
            		  K.push_back(Tr(s,getIndexOfState(sc),PI*(CTR((sa[C]-1),a-1))));
            		  Kmap[MyTr(s,getIndexOfState(sc))] = true;
            	  } else {
            		  refused++;
            	  }


              } else {

            	  if ( Kmap.find(MyTr(s,getIndexOfState(sc))) == Kmap.end()) {
            		  K.push_back(Tr(s,getIndexOfState(sc),PI));
            		  Kmap[MyTr(s,getIndexOfState(sc))] = true;
            		  nonzero++;
            	  }

              }

          }
      }
      T[a].setFromTriplets(K.begin(),K.end());


      T[a].finalize();

  }
  cout << "Done!" << endl;
  delete sa;
  delete sc;

}

int MDP::checkT() {

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
         Q.col(a) = R[a] + T[a]*V;
         //Q.col(a) += R[a];
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

/*
 * main.cc
 *
 *  Created on: Jul 30, 2012
 *      Author: ftruzzi
 */

#define EIGEN_YES_I_KNOW_SPARSE_MODULE_IS_NOT_STABLE_YET

#include <iostream>
#include <fstream>
#include "Simulator.h"
#include <Eigen/Dense>
#include "MDP.h"
#include <jsoncpp/json.h>

using namespace std;
using namespace Eigen;


int main(int argc, char **argv) {
	setNbThreads(3);
	Json::Value root;
	std::ifstream file("../input.json");
	file >> root;

	int B = atoi(root["B"].toStyledString().c_str());
	int C = atoi(root["C"].toStyledString().c_str());
	int G = atoi(root["G"].toStyledString().c_str());
	int tau = atoi(root["tau"].toStyledString().c_str());
	int n_means = atoi(root["n_means"].toStyledString().c_str());
	double prequest = atof(root["Prequest"].toStyledString().c_str());
	double Pg[G];

	Json::Value pg;
	pg = root["Pg"];

	for (unsigned int i = 0; i < pg.size(); i++)
		Pg[i] = atof(pg[i].toStyledString().c_str());

	MatrixXd CTR(G,C);

	for ( int i = 0; i < G; i++)
		for (int j = 0; j < C; j++)
			CTR(i,j) = atof(root["CTR"][i][j].toStyledString().c_str());


	VectorXd CPC(C);

	for ( int i = 0; i < C; i++)
		CPC(i) = atof(root["CPC"][i].toStyledString().c_str());



	MDP k(C,G,B,tau,prequest,CTR,Pg,CPC);


	k.PopulateMtx();

	k.ValueIteration();

	Simulator a(C,G,B,CTR,CPC,tau,n_means,prequest,Pg,&k);
	a.Simulate();

	ofstream sim("sim.mtx");
	sim << k.V;
	sim.close();

	ofstream policy("policy.mtx");
	policy << k.policy;
	policy.close();

	ofstream t0("t0.mtx");
	t0 << k.T[0].toDense();
	t0.close();

	ofstream t1("t1.mtx");
	t1 << k.T[1].toDense();
	t1.close();

	ofstream t2("t0.mtx");
	t2 << k.T[2].toDense();
	t2.close();

	ofstream t3("t0.mtx");
	t3 << k.T[3].toDense();
	t3.close();




	return 0;
}


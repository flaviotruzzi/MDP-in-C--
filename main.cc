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
	MYTYPE prequest;
	std::stringstream ss(root["Prequest"].toStyledString().c_str());
	MYTYPE x;
	ss >> x;
	prequest = x;
	MYTYPE Pg[G];

	Json::Value pg;
	pg = root["Pg"];

	for (unsigned int i = 0; i < pg.size(); i++) {
		std::stringstream ss(pg[i].toStyledString().c_str());
		MYTYPE x;
		ss >> x;
		Pg[i] = x;
	}
	MatrixXld CTR(G,C);

	for ( int i = 0; i < G; i++)
		for (int j = 0; j < C; j++) {
			std::stringstream ss(root["CTR"][i][j].toStyledString().c_str());
			MYTYPE x;
			ss >> x;
			CTR(i,j) = x;
		}



	VectorXld CPC(C);

	for ( int i = 0; i < C; i++) {
		std::stringstream ss(root["CPC"][i].toStyledString().c_str());
		MYTYPE x;
		ss >> x;
		CPC(i) = x;
	}

	MDP k(C,G,B,tau,prequest,CTR,Pg,CPC);


	k.PopulateMtx();

	k.ValueIteration();

	Simulator a(C,G,B,CTR,CPC,tau,n_means,prequest,Pg,&k);
	a.Simulate();

	ofstream sim("result.mtx");
	sim << a.values;
	sim.close();

	ofstream simm0("sim0.mtx");
	simm0 << a.simulations[0];
	simm0.close();

	ofstream simm1("sim1.mtx");
	simm1 << a.simulations[1];
	simm1.close();

	ofstream policy("policy.mtx");
	policy << k.policy;
	policy.close();


	return 0;
}


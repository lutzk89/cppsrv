/*
 * neuralnet.h
 *
 *  Created on: 21.10.2015
 *      Author: lutzk
 */

#ifndef NNET_NEURALNET_H_
#define NNET_NEURALNET_H_
#include<dataprovider.h>
#include "/usr/include/c++/5.2.0/memory"
#include "/usr/include/math.h"
#include "../service/dataprovider.h"
#include <algorithm>
#include <math.h>
#include <random>

class neuralnet {
private:
	double* w;
	double* b;
	double* z;
	double* a;
	double* d;
	double learningRate;
	int nin;
	int nout;
	int nsets;
	int nhi;
	dirDataProvider* provider;
public:
	neuralnet(int newNin, int newNout, int newNhi)
	~neuralnet()
	double backprop(double s)
	int initialize() { }
	int feedforward() { }
	int randomInit() {	}
	int mutate() {	}
	int getNumOfLayers() {	}
	int getSizeOfW() {	}
	int getSizeOfB() {	}
	int getSizeOfZ() {	}
	int getBaddress(int node,int layer) { }
	int getZaddress(int node,int layer,int dataset) { }
	int getWaddress(int node1,int node2,int layer) {	}
	double feedForward(int dset) { }
	double propFunc(double x) {	}
	double propFuncPrime(double x) { }
	int gradientStep(int dset) {
	}
};



#endif /* NNET_NEURALNET_H_ */

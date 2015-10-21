/*
 * neuralnet.h
 *
 *  Created on: 21.10.2015
 *      Author: lutzk
 */

#ifndef NNET_NEURALNET_H_
#define NNET_NEURALNET_H_


class neuralnet {
	public:
	neuralnet(int newNin, int newNout, int newNhi,dataProvider* provider);
	int backprop();
	int initialize();
	int feedforward();
};



#endif /* NNET_NEURALNET_H_ */

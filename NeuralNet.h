#ifndef NEURALNET_H_
#define NEURALNET_H_

#include <iostream>

#include "BackPropNN.h"
#include "Sig.h"
#include "Database.h"

using namespace std;

class NeuralNet
{
	BackPropNN *bp;
	Database db;
	int midNodes;	// number of nodes (neurons) in the middle (hidden) layer
	int numTr;		// numTr stores the number of training signatures loaded
	int numRes;		// number of possible results (number of different signatures)
	long maxIter;	// maximum number of iterations during training
	double MSE;
	
	// Neural Network Configuration Options
	double alpha;
	double beta;
	double thresh;
	int numLayers;
	int *layerSize;
	
	bool train(string trainPath, TrainData *trainData);	// train the neural network
	
public:
	NeuralNet(int nodes, int iter, double b, double a, double t, string trainPath);
	NeuralNet(string filePath);
	int test(string filePath, double *prob);	// test a signature
	int testDir(string dirPath, int *nTest);	// test a directory of signatures
	string whoIs(int index);
	int getNum();
	void save(string filePath);
	void load(string filePath);
	virtual ~NeuralNet();
};

#endif /*NEURALNET_H_*/

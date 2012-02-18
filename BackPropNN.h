#ifndef CBACKPROP_H_
#define CBACKPROP_H_

#include <iostream>
#include <cmath>
#include <ctime>
#include <fstream>

using namespace std;

class BackPropNN
{
	double **out;		// output of each neuron
	double **delta;		// delta - the error value for each neuron

	double ***weight;	// weights of each link
	double ***prevDwt;	// previous weights
	int nLayers;		// number of layers in the NN (input, middle, output)
	int *layerSize;		// size of each layer

	double beta;		// beta - the "learning rate"
	double alpha;		// alpha - the "momentum"

	double sigmoid(double x);	//	sigmoid function
	void allocateWeights(void);
	void freeWeights(void);

public:
	// constructors - create the net
	BackPropNN(int nl, int *sz, double b, double a);
	BackPropNN(string filePath);
	// backpropogates error for one set of input (training)
	void bpgt(double *in, double *tgt); 
	// feeds forward activations for one set of inputs
	void ffwd(double *in);
	// returns the mean square error of the net
	double mse(double *tgt) const;		
	// returns i'th output of the net
	double Out(int i) const;
	// save the net to a file
	bool save(string filepath);
	// load the net from a file
	bool load(string filepath);
	// destructor - frees memory
	~BackPropNN();
};

#endif /*CBACKPROP_H_*/

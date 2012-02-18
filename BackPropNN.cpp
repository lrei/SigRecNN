/*
 * A Backpropagating Multilayered Feedforward Neural Network
 * Adapted from code by Tejpal Chhabra (http://indore.sancharnet.in/tejpal/)
 */

#include "BackPropNN.h"

/*
 * constructor - allocates memory and initializes the neural network
 * INPUT
 * 		nl	- number of layers
 * 		sz	- array containing the size of each layer
 * 		b	- beta (learning rate)
 * 		a	- alpha (momentum)
 */
BackPropNN::BackPropNN(int nl, int *sz, double b, double a):beta(b), alpha(a)
{
	/*	set number of layers and their sizes */
	nLayers = nl;
	layerSize = new int [nLayers];
	
	for(int ii = 0; ii < nLayers; ii++) {
		layerSize[ii] = sz[ii];
	}
	
	allocateWeights();	// allocate memory for the weights


	/*	
	 * Generate random weights to initialize NN
	 */
	srand((unsigned int) time(NULL));	// use current time as seed
	for(int ii = 1; ii < nLayers; ii++)		// layers
		// jj - neuron of the "current" layer
		for(int jj = 0; jj < layerSize[ii]; jj++)	// neurons
			// kk - neuron of the "previous" (ii-1) layer: jj-link->kk
			// each jj neuron is connected to every kk neuron
			// every neuron of a layer connects to all neurons of the next layer
			for(int kk = 0; kk < layerSize[ii-1]+1; kk++)	// links
				// RAND_MAX is usually 32767
				weight[ii][jj][kk]= (double) rand()/(RAND_MAX/2) - 1;

	//	initialize previous weights to 0 for the first iteration
	for(int ii = 1; ii < nLayers; ii++)
		for(int jj = 0; jj < layerSize[ii]; jj++)
			for(int kk = 0; kk < layerSize[ii-1]+1; kk++)
				prevDwt[ii][jj][kk] = (double) 0.0;

/*
 * NOTE
 *  The following variables that would apply to the input layer (layer 0) are 
 * unused because the input layer only stores the input and thus there is no 
 * weigth or delta associated with it:
 * delta[0]
 * weight[0]
 * prevDwt[0]
 */
}

BackPropNN::BackPropNN(string filePath)
{
	nLayers = 0;
	
	load(filePath);
}

/*
 * 	sigmoid function (aka logistic function)
 *  1 / (1 + e^-x)
 *  Will serve as our activation function
 *  The activation function will make the neuron inactive (output near 0) when 
 *  the "wrong" inputs are given and active (near 1) when the "right" inputs 
 *  are given.
 *  The input is the sum of the weighted activations coming from the neurons
 *  of the previous layer (via the "links") 
 */
double BackPropNN::sigmoid(double x)
{
		return (double) (1 / (1 + exp(-x)));
}

/*	
 * Mean square error
 * it is used as a measure of how well the neural net has learned.
 */
double BackPropNN::mse(double *tgt) const
{
	double mse = 0;
	for(int ii =0; ii < layerSize[nLayers-1]; ii++) {
		mse += (tgt[ii]-out[nLayers-1][ii])*(tgt[ii]-out[nLayers-1][ii]);
	}
	return mse/2;
}


/*
 * 	returns i'th output of the net
 */
double BackPropNN::Out(int i) const
{
	return out[nLayers-1][i];
}

/*
 *  feed forward one set of input
 */
void BackPropNN::ffwd(double *in)
{
	double sum;

	//	assign content to input layer
	for(int ii = 0; ii < layerSize[0]; ii++) {
		out[0][ii] = in[ii];  // output_from_neuron(i,j) Jth neuron in Ith Layer
		//cout << "out[0][ii] = " << in[ii] << endl;
	}

	/*	assign output (activation) value to each neuron */
	for(int ii = 1; ii < nLayers; ii++) {		// layer
		for(int jj = 0; jj < layerSize[ii]; jj++) { // neuron
			sum = 0.0;
			for(int kk = 0; kk < layerSize[ii-1]; kk++) {
				// for input from each neuron in preceeding layer
				sum+= out[ii-1][kk] * weight[ii][jj][kk];	// Apply weight to inputs and add to sum
			}
			sum += weight[ii][jj][layerSize[ii-1]];	// Apply bias
			out[ii][jj] = sigmoid(sum);				// Apply sigmoid function
			//cout << out[ii][jj] << endl;
		}
	}
}

/*	
 * backpropogate errors from the output layer
 * (this is done during training)
 * INPUT
 * 		*in  - pointer to the data array
 * 		*tgt - pinter to the array of correct outputs
 */
void BackPropNN::bpgt(double *in, double *tgt)
{
	double sum;

	//	update output values for each neuron
	ffwd(in);

	//	find delta for output layer
	for(int ii = 0; ii < layerSize[nLayers-1]; ii++) {
		delta[nLayers-1][ii] = out[nLayers-1][ii] *
			(1-out[nLayers-1][ii])*(tgt[ii]-out[nLayers-1][ii]);
	}

	//	find delta for hidden layers	
	for(int ii = nLayers-2; ii > 0; ii--) {
		for(int jj = 0; jj < layerSize[ii]; jj++) {
			sum = 0.0;
			for(int kk = 0; kk < layerSize[ii+1]; kk++){
				sum += delta[ii+1][kk]*weight[ii+1][kk][jj];
			}
			delta[ii][jj] = out[ii][jj]*(1-out[ii][jj])*sum;
		}
	}

	//	apply momentum ( does nothing if alpha=0 )
	for(int ii = 1; ii < nLayers; ii++) {
		for(int jj = 0; jj < layerSize[ii]; jj++) {
			for(int kk = 0; kk < layerSize[ii-1]; kk++) {
				weight[ii][jj][kk] += alpha*prevDwt[ii][jj][kk];
			}
			weight[ii][jj][layerSize[ii-1]] += alpha*prevDwt[ii][jj][layerSize[ii-1]];
		}
	}

	/*	Adjust the Weights */
	// this is were the "learning rate" beta is applied
	for(int ii = 1; ii < nLayers; ii++) {
		for(int jj = 0; jj < layerSize[ii]; jj++) {
			for(int kk = 0; kk < layerSize[ii-1]; kk++) {
				prevDwt[ii][jj][kk] = beta*delta[ii][jj]*out[ii-1][kk];
				weight[ii][jj][kk] += prevDwt[ii][jj][kk];
			}
			prevDwt[ii][jj][layerSize[ii-1]] = beta*delta[ii][jj];
			weight[ii][jj][layerSize[ii-1]] += prevDwt[ii][jj][layerSize[ii-1]];
		}
	}
}

/*
 * saves the neural net to a file
 */
bool BackPropNN::save(string filepath)
{
	int ii, jj, kk;
	ofstream file(filepath.c_str());
	
	
	/* Write configuration */
	file << nLayers << endl << beta << endl << alpha << endl;
	for (ii = 0; ii < nLayers; ii++)
		file << layerSize[ii] << " ";	// " " will have to be ignored
	file << endl;	// endl will also have to be ignored i.e. ignore.in(1)
	
	/* Write the weights */ 
	for(int ii = 1; ii < nLayers; ii++)		// layers
		for(jj = 0; jj < layerSize[ii]; jj++)	// neurons
			for(kk = 0; kk < layerSize[ii-1]+1; kk++)	// links
				file << weight[ii][jj][kk] << " "; // " " again
	
	file.close();
	return true;
}

bool BackPropNN::load(string filepath)
{
	int ii, jj, kk;
	ifstream file(filepath.c_str());
	
	if (nLayers != 0) {	// overwriting net
		freeWeights();
		delete[] layerSize;
	}
	
	/* Read configuration */
	file >> nLayers;
	layerSize = new int [nLayers];
	file.ignore();
	
	file >> beta;
	file.ignore();
	file >> alpha;
	file.ignore();
	
	for (ii = 0; ii < nLayers; ii++) {
		file >> layerSize[ii];
		file.ignore();
	}
	file.ignore();
	
	/* Read the weights */ 
	allocateWeights();
	for(int ii = 1; ii < nLayers; ii++)		// layers
		for(jj = 0; jj < layerSize[ii]; jj++)	// neurons
			for(kk = 0; kk < layerSize[ii-1]+1; kk++) {	// links
				file >> weight[ii][jj][kk];
				file.ignore();
			}
	
	
	file.close();
	return true;
}

void BackPropNN::allocateWeights(void)
{
		/*	allocate memory for the output of each neuron */
	out = new double* [nLayers];
	
	for(int ii = 0; ii < nLayers; ii++) {
		out[ii] = new double [layerSize[ii]];
	}


	/*	allocate memory for the delta (error) of each neuron */
	delta = new double* [nLayers];

	for(int ii = 1; ii < nLayers; ii++) {
		delta[ii] = new double [layerSize[ii]];
	}


	/*	allocate memory for the weights */
	weight = new double** [nLayers];

	for(int ii = 1; ii < nLayers; ii++) {
		weight[ii] = new double* [layerSize[ii]];
	}
	for(int ii = 1; ii < nLayers; ii++) {	// layers
		for(int jj = 0; jj < layerSize[ii]; jj++) {	// neurons
			weight[ii][jj] = new double [layerSize[ii-1]+1];
		}
	}

	/*	allocate memory for previous weights */
	prevDwt = new double**[nLayers];

	for(int ii = 1; ii < nLayers; ii++) {
		prevDwt[ii] = new double* [layerSize[ii]];
	}
	for(int ii = 1; ii < nLayers; ii++) {
		for(int jj = 0; jj < layerSize[ii]; jj++) {
			prevDwt[ii][jj] = new double [layerSize[ii-1]+1];
		}
	}
}

void BackPropNN::freeWeights(void)
{
		//	free out
	for(int ii = 0; ii < nLayers; ii++)
		delete[] out[ii];
	delete[] out;

	//	free delta
	for(int ii = 1; ii < nLayers; ii++)
		delete[] delta[ii];
	delete[] delta;

	//	free weight
	for(int ii = 1; ii < nLayers; ii++)
		for(int jj = 0; jj < layerSize[ii]; jj++)
			delete[] weight[ii][jj];
	for(int ii = 1; ii < nLayers; ii++)
		delete[] weight[ii];
	delete[] weight;

	//	free prevDwt
	for(int ii = 1; ii < nLayers; ii++)
		for(int jj = 0; jj < layerSize[ii]; jj++)
			delete[] prevDwt[ii][jj];
	for(int ii = 1; ii < nLayers; ii++)
		delete[] prevDwt[ii];
	delete[] prevDwt;
	
}

/*
 * destructor - frees the memory used by the neural network, effectively
 * destroying it.
 */
BackPropNN::~BackPropNN()
{
	freeWeights();
	//	free layer info
	delete[] layerSize;
}


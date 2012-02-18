#include "NeuralNet.h"

NeuralNet::NeuralNet(int nodes, int iter, double b, double a, double t, string trainPath)
{
	TrainData *trainData;
	
	midNodes = nodes;
	maxIter = iter;
	
	beta = b;
	alpha = a;
	thresh = t;
	numLayers = 3;	// currently always 3
	
	/* Load Training Data */
	//cout << "Loading training data...";
	trainData = db.loadTrainDataFromDir(trainPath, &numTr);
	
	numRes = db.tableSize();	/* the number of possible results is determined
								 * by asking the DB how many signatures are
								 * known */
	
	// 32xmidNoes + midNodes*numRes = numRes * nTrainEx
	layerSize = new int [numLayers];
	layerSize[0] = 8*2*2;
	layerSize[1] = midNodes;
	layerSize[2] = numRes;
	
	// Create the neural net
	bp = new BackPropNN(numLayers, layerSize, beta, alpha);

	train(trainPath, trainData);
	
}

NeuralNet::NeuralNet(string filePath)
{
	load(filePath);
	
	numRes = db.tableSize();

}


bool NeuralNet::train(string trainPath, TrainData *trainData)
{
	double **answer;
	int max, ii;
	
	
	// prepare the array with the correct answer for each signature
	answer = new double* [numTr];
	
	max = -1;
	for (ii = 0; ii < numTr; ii++) {
		answer[ii] = new double [numRes];
		for (int jj = 0; jj < numRes; jj++) {
			if (jj == (int) trainData[ii].value)
				answer[ii][jj] = 1;
			else 
				answer[ii][jj] = 0;
		}
		if (max != (int)trainData[ii].value) {
			for(int jj = 0; jj < numRes; jj++)
				max = (int)trainData[ii].value;
		}
	}
	
	
	/* Train the net */
	for (ii = 0; ii < maxIter ; ii++) {
		bp->bpgt(trainData[ii%numTr].sigArr, answer[ii%numTr]);

		if ((MSE = bp->mse(answer[ii%numTr])) < thresh) {	// Training Complete
			//cout << "MSE = " << MSE << endl;
			break;	// Stop
		}

	}
	
	return true;	
}

int NeuralNet::testDir(string dirPath, int *nTest)
{
	Database testDb;
	TrainData *testData;
	double *test, temp = 0;
	int ii, jj, max, correct;
	
	
	testData = testDb.loadTrainDataFromDir(dirPath, nTest);
	
	correct = 0;
	
	for(jj = 0; jj < *nTest; jj++) {
		temp = 0; max = 0;
		/* Load the test data */	
		test = testData[jj].sigArr;
	
		//cout << endl << "\t\t\tTesting for " << testData[jj].name << "..." << endl;	

		/* feed the test data to the net */
		bp->ffwd(test);
	

		for (ii = 0 ; ii < numRes ; ii++) {
			 // the results are the values at the output nodes
			 //cout << db.tableLookup(ii) << ": " << bp->Out(ii)*100 << "%" << endl;
			if (bp->Out(ii) > temp) {
				/* the highest value of the output nodes 
				 * will determine the actual result
				 * i.e. who the test signature belongs to */
				temp = bp->Out(ii);
				max = ii;
			}
		}
		if (testData[jj].name == db.tableLookup(max)) {
			correct++;
		}
	}
	
	return correct;
}

int NeuralNet::test(string filePath, double *prob)
{
	Sig testSig;
	double temp;
	double *test;
	int max, ii;
	
	testSig.load(filePath);
	test = testSig.toArray();
	
	
	/* feed the test data to the net */
	bp->ffwd(test);

	for (ii = 0 ; ii < numRes ; ii++) {
		if ((prob[ii] = bp->Out(ii)) > temp) {
			/* the highest value of the output nodes 
			 * will determine the actual result
			 * i.e. who the test signature belongs to */
			temp = bp->Out(ii);
			max = ii;
		}
	}
	
	return max;
}

string NeuralNet::whoIs(int index)
{
	return db.tableLookup(index);
}

int NeuralNet::getNum()
{
	return numRes;
}

void NeuralNet::save(string filePath) {
	string bpFile;
	string dbFile;
	
	bpFile = filePath + ".bp";
	dbFile = filePath + ".db";
	
	bp->save(bpFile);
	db.save(dbFile);
}

void NeuralNet::load(string filePath) {
	string base;
	string bpFile;
	string dbFile;
	int endpos;
	
	endpos = filePath.find_last_not_of(".");
	base = filePath.substr(0, endpos - 1);
	
	bpFile = filePath + ".bp";
	dbFile = filePath + ".db";
	
	bp = new BackPropNN(bpFile);
	db.load(dbFile);
}

NeuralNet::~NeuralNet()
{
}

#include "anyoption.h"
#include "NeuralNet.h"
#include <math.h>

int main( int argc, char* argv[] )
{
	NeuralNet *nn;
	string trainPath;
	string testDirPath;
	string savePath;
	string loadPath;
	string temp;
	
	double alpha, beta, thresh;
	double *probs;
	long maxIter;
	int nodes, res, ii, jj, numRes, certainty;
	
	bool verbose;
	bool train;
	bool load;
	bool save;
	bool bulk;

	// SET DEFAULTS
	alpha = 0.1;
	beta = 0.3;
	maxIter = 30000;
	nodes = 30;
	thresh =  0.0001;
	verbose = false;
	train = false;
	load = false;
	save = false;
	bulk = false;

	// CREATE AN OBJECT
	AnyOption *opt = new AnyOption();

	// SET PREFERENCES
	//opt->autoUsagePrint(true); /* print usage for bad options */

	// SET THE USAGE/HELP
	opt->addUsage( "Usage: " );
	opt->addUsage( "" );
	opt->addUsage( " -h  --help  			Prints this help " );
	opt->addUsage( " -t  --train traindir	Train network with images from traindir " );
	opt->addUsage( " -d  --bulk	testdir		Test an entire directory of signatures " );
	opt->addUsage( " -s  --save file.ann  	Save the network " );
	opt->addUsage( " -l  --load file.ann	Load the network " );
	opt->addUsage( " -a  --alpha			Value of alpha (Momentum) " );
	opt->addUsage( " -b  --beta				Value of beta (Learning Rate) " );
	opt->addUsage( " -e  --threshold		Value of the Threshold " );
	opt->addUsage( " -m  --max				Maximum Iterations " );
	opt->addUsage( " -n  --nodes			Number of nodes in the middle layer " );
	opt->addUsage( " -c  --certainty %		Minimum certainty " );
	opt->addUsage( " -v  --verbose			Show full output " );
	opt->addUsage( "Example: nn -l lab.ann -c 80 -v sig1.bmp sig2.bmp" );
	opt->addUsage( "" );

	// SET THE OPTION STRINGS/CHARACTERS

	opt->setFlag("help", 'h' );
	opt->setFlag("verbose", 'v' );
	
	opt->setOption("train", 't');
	opt->setOption("bulk", 'd');
	opt->setOption("save", 's');
	opt->setOption("load", 'l');
	opt->setOption("alpha", 'a');
	opt->setOption("beta", 'b');
	opt->setOption("threshold", 'e');
	opt->setOption("max", 'm');
	opt->setOption("nodes", 'n');
	opt->setOption("certainty", 'c');
		
	// PROCESS THE COMMANDLINE
	// go through the command line and get the options
	opt->processCommandArgs(argc, argv);

	if (!opt->hasOptions()) { // print usage if no options
		opt->printUsage();
		delete opt;
		return 0;
	}

	// GET THE VALUES
	if (opt->getFlag("help") || opt->getFlag('h')) {
		opt->printUsage();
	}
	if (opt->getFlag( "verbose") || opt->getFlag('v')) {
		verbose = true;
	}
	if (opt->getValue('a') != NULL  || opt->getValue("alpha") != NULL) {
		temp = opt->getValue('a');
		alpha = atof(temp.c_str());
	}
	if (opt->getValue('b') != NULL  || opt->getValue("beta") != NULL) {
		temp = opt->getValue('b');
		beta = atof(temp.c_str());
	}
	if (opt->getValue('e') != NULL  || opt->getValue("thresh") != NULL) {
		temp = opt->getValue('e');
		thresh = atof(temp.c_str());
	}
	if (opt->getValue('m') != NULL  || opt->getValue("max") != NULL) {
		temp = opt->getValue('m');
		maxIter = atol(temp.c_str());
	}
	if (opt->getValue('n') != NULL  || opt->getValue("nodes") != NULL) {
		temp = opt->getValue('n');
		nodes = atoi(temp.c_str());
	}
	if (opt->getValue('c') != NULL  || opt->getValue("certainty") != NULL) {
		temp = opt->getValue('c');
		certainty = atoi(temp.c_str());
	}
	if (opt->getValue('s') != NULL  || opt->getValue("save") != NULL) {
		savePath = opt->getValue('s');
		save = true;
	}
	if (opt->getValue('l') != NULL  || opt->getValue("load") != NULL) {
		loadPath = opt->getValue('l');
		load = true;
	}
	if (opt->getValue('t') != NULL  || opt->getValue("train") != NULL) {
		trainPath = opt->getValue('t');
		train = true;
	}
	if (opt->getValue('d') != NULL  || opt->getValue("bulk") != NULL) {
		testDirPath = opt->getValue('d');
		bulk = true;
	}
	
	// VERIFY ARGUMENT SANITY
	if (load && train) {
		cerr << "Invalid options: train or load - not both!" << endl;
		return 1;
	}
	if (!load && !train) {
		cerr << "The Neural Network must be loaded or trained." << endl;
		return 2;
	}
	if ((alpha < 0) || (beta < 0) || (thresh < 0) || (nodes < 0) || (maxIter < 0)) {
		cerr << "Can not assign negative values to parameters." << endl;
		return 3;
	}
	
	// EXECUTE
	if (train) {
		cout << "Training... ";
		cout.flush();
		nn = new NeuralNet(nodes, maxIter, beta, alpha, thresh, trainPath);
		cout << "trained." << endl;
		cout.flush();
	}
	if (load) {
		cout << "Loading... ";
		cout.flush();
		nn = new NeuralNet(loadPath);
		cout << "loaded." << endl;
		cout.flush();
	}
	if (save) {
		cout << "Saving... ";
		cout.flush();
		nn->save(savePath);
		cout << "saved." << endl;
		cout.flush();
	}
	
	numRes = nn->getNum();
	probs = new double [numRes];
	
	if (bulk) {
		cout << "Bulk testing... " << endl;
		cout.flush();
		res = nn->testDir(testDirPath, &ii);
		cout << "summary: " << res << "/" << ii << endl;
		cout << "finished bulk test." << endl;
		cout.flush();
	}
	
	if (verbose) { // display network configuration
		cout << "Configuration: " << endl
		<< "\tnodes\t= " << nodes << endl
		<< "\talpha\t= " << alpha << endl
		<< "\tbeta\t= " << beta << endl
		<< "\tthresh\t= " << thresh << endl 
		<< "\tmaxIter\t= " << maxIter << endl
		<< endl;
		cout.flush();
	}
		
		
	// arguments = sigs to test
	for(jj = 0 ; jj < opt->getArgc() ; jj++ ) { // test
		temp = opt->getArgv(jj);
		res = nn->test(temp, probs);
		cout << "Testing " << temp << endl;
		if (verbose) {	// display probabilities of all possible sigs
			for (ii = 0; ii < numRes; ii++) {
				cout << nn->whoIs(ii) << ": " << probs[ii]*100 << "%" << endl;
			}
		}
		// display result
		cout << "Result = " << nn->whoIs(res) << " (" << probs[res]*100 << ")" << endl << endl;
	}

	// DONE
	delete opt;

}

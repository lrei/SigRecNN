#ifndef SIG_H_
#define SIG_H_

#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include "BMPextra.h"

using std::string;

class Sig
{
	BMP bsig;			// holds the signature
	BMP proj[4];		// holds the projections of the signature
	bool normalized;	// is normalized ?
	bool projected;		// do the projections exist ?
	
	bool normalize();	// normalizes the signature
	bool projections();	// extracts projections from the signature
	
	double TERM;		// value that terminates the sig array
	
public:
	Sig();
	Sig(string path);

	int getInDepth();
	int getInWidth();
	int getInHeight();
	int getFactor();
	
	bool load(string path);
	bool isnormalized();
	bool isprojected();
	bool loadNormalized(string path);	// TODO
	bool saveNormalized(string path);
	bool saveProjections(string path);
	bool loadProjections(string path);	// TODO
	double *toArray();
	bool saveArray(string filepath);
	virtual ~Sig();
};

#endif /*SIG_H_*/

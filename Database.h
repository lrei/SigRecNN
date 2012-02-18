#ifndef DATABASE_H_
#define DATABASE_H_

#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <vector>
#include <string>
#include <iostream>


#include "Sig.h"
#include "DataStructures.h"

using namespace std;

class Database
{
	vector<string> table;
	
public:
	Database();
	Database(string ffilePath);
	bool getFileList(string dir, vector<string> &files);
	string filenameToName(string filename);
	int tableLookup(string name);
	string tableLookup(unsigned int index);
	int tableSize();
	TrainData *loadTrainDataFromDir(string dir, int *n);
	bool save(string filePath);
	bool load(string filePath);
	virtual ~Database();
};

#endif /*DATABASE_H_*/

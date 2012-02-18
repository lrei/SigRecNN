#include "Database.h"

Database::Database()
{
}

Database::Database(string filePath)
{
	load(filePath);
}

/*
 * Get a list of files in a directory
 * adapted from code written by jtshaw (http://www.linuxquestions.org)
 */
bool Database::getFileList(string dir, vector<string> &files)
{
	DIR *dp;
    struct dirent *dirp;
    string filename, extension;
    int startpos, len;
    
    if((dp  = opendir(dir.c_str())) == NULL) {
        cerr << "Error(" << errno << ") opening " << dir << endl;
        return false;
    }

    while ((dirp = readdir(dp)) != NULL) {
    	filename = string(dirp->d_name);	// convert from c_str to c++ string
    	startpos = filename.find_last_of('.');
    	startpos++;	// skip the .
    	len = filename.size() - startpos;
    	extension = "";
    	extension.append(filename, startpos, len);	// get extension
    	if (extension == "BMP" || extension == "bmp")
        	files.push_back(filename);
    }
    
    closedir(dp);
    return true;
}

/*
 * Extract name from filename
 * The name is everything between the last / and -
 * TODO: make this windows-compatible
 */
string Database::filenameToName(string filename)
{
	string name = "";
	int startpos, endpos;
	
	startpos = filename.find_last_of('/');
	startpos++;	// skip the /
	endpos = filename.find('-', startpos);
	// get everything between the last / and -
	name.append(filename, startpos, endpos-startpos);
	return name;
}

/*
 * Name Table lookup function - returns the position of name in the table
 * adds name to the table if it isn't found
 */
int Database::tableLookup(string name)
{
	unsigned int ii;
	bool found = false;
	
	for(ii = 0; ii < table.size(); ii++)
		if (table[ii] == name) {
			found = true;
			break;
		}
	// if it isn't found, add it to the table
	if (!found)
		table.push_back(name);
	
	return ii;
}

/*
 * Name Table lookup function - returns name in the position
 */
string Database::tableLookup(unsigned int index)
{
	return table[index];
}

/*
 * Table size - returns the number of entries in the table
 */
int Database::tableSize()
{
	return table.size();
}

/*
 * Load Train Data (Signatures and respective names) from a directory
 * Returns the number of signatures read
 * TODO: make this windows compatible
 */
TrainData *Database::loadTrainDataFromDir(string dir, int *n)
{
	Sig sig;
	vector<string> files = vector<string>();
	string fname, temp;
	char buf[1024];
	unsigned int ii;
	TrainData *data;

    getFileList(dir, files);
    
    data = new TrainData [files.size()];
    getcwd(buf, 1024);		// save current dir
//    cout << "Changing CWD to " << dir << "." << endl;
    chdir(dir.c_str());		// change current dir to data dir
    for (ii = 0; ii < files.size(); ii++) {
        fname = files[ii];
//        cout << "Reading " << fname << "." << endl;
        sig.load(fname);
        data[ii].name = filenameToName(files[ii]);	// Get Name from sig file
        data[ii].sigArr = sig.toArray();			// convert sig to array
        data[ii].value = (double) tableLookup(data[ii].name);	/* get value
        														 * (table index)
        														 */
    }
//    cout << "Back to previous CWD." << endl;
    chdir(buf);			// change back to original working dir
//    cout << "Read a total of " << ii << " files." << endl;
    *n = ii;
    return data;
}

bool Database::save(string filePath)
{
	ofstream file(filePath.c_str());
	unsigned int ii;
	
	for(ii = 0; ii < table.size(); ii++)
		file << table[ii] << endl;
	
	file.close();
	return true;
}

bool Database::load(string filePath)
{
	ifstream file(filePath.c_str());
	string temp;

	table.clear();
	
	while (!file.eof()) {
		getline (file, temp);
		table.push_back(temp);
	}
	
	file.close();
	return true;
}	

Database::~Database()
{
}

#ifndef DATASTRUCTURES_H_
#define DATASTRUCTURES_H_

#include <string>
#include "Sig.h"

/* Associates a signature with a name and a value */
typedef struct _TrainData {
	double *sigArr;
	string name;
	double value;
} TrainData;

#endif /*DATASTRUCTURES_H_*/

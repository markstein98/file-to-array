#ifndef FILETOARRAY_H
#define FILETOARRAY_H

#include <stdio.h>
#include <stdlib.h>

class MyData{
	public:
	// methods
	int getSize(void);
	float* getData(void);
	// attributes
	
	// constructor
	MyData(const char* filename);
	private:
	// methods
	FILE* myfopen(const char* filename);
	int countData(const char* filename);
	float* readData(const char* filename);
	// attributes
	int _ndati;
	float* _data;
};

#endif

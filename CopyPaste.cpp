/* CopyPaste.cpp
 * 
 * Copyright 2019 Marco Aliberti
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 */

#include <stdio.h>
#include <stdlib.h>

class MyData{
	public:
	// methods
	unsigned int getSize(void);
	unsigned int getOrigSize(void);
	float* getData(void);
	float* getOrigData(void);
	void removeFirstData(unsigned int num);
	void removeData(unsigned int index);
	void removeLastData(unsigned int num);
	void printData(void);
	void printData(int index);
	void printOrigData(void);
	void printOrigData(int index);
	// attributes
	
	// constructor
	MyData(float value = 0.0, int size = 1);
	MyData(const char* filename);
	MyData(MyData* oldData);
	private:
	// methods
	FILE* myfopen(const char* filename);
	unsigned int countData(const char* filename);
	float* readData(const char* filename);
	// attributes
	unsigned int _ndati, _ndatiOrig;
	float *_data, *_dataOrig;
};

MyData::MyData(float value, int size){
	_ndatiOrig = size;
	_ndati = size;
	_dataOrig = (float *) malloc(_ndati * sizeof(float));
	_data = (float *) malloc(_ndati * sizeof(float));
	for(uint i=0;i<_ndati;i++){
		_dataOrig[i] = value;
		_data[i] = value;
	}
}

MyData::MyData(const char* filename){
	_ndatiOrig = countData(filename);
	_ndati = _ndatiOrig;
	_dataOrig = readData(filename);
	_data = (float *) malloc(_ndati * sizeof(float));
	_data = (float *) memcpy((void *)_data, (void *)_dataOrig, _ndati * sizeof(float));
}

MyData::MyData(MyData* oldData){
	_ndatiOrig = oldData->getSize();
	_ndati = _ndatiOrig;
	_dataOrig = (float *) malloc(_ndati * sizeof(float));
	_data = (float *) malloc(_ndati * sizeof(float));
	_dataOrig = (float *) memcpy((void *)_dataOrig, (void *)oldData->getData(), _ndati * sizeof(float));
	_data = (float *) memcpy((void *)_data, (void *)_dataOrig, _ndati * sizeof(float));
}

// private methods

FILE* MyData::myfopen(const char *filename){
	FILE* fp;
	fp = fopen(filename, "r");
	if(fp == NULL){
		fprintf(stderr,"Error while opening file %s", filename);
		fprintf(stderr,"\nPress any key to exit.\n");
		fflush(stdin);
		getchar();
		exit(1);
	}
	return fp;
}

unsigned int MyData::countData(const char* filename){
	FILE* file;
	unsigned int n;
	float swap;
	
	file = myfopen(filename);
	for(n=0;fscanf(file,"%f",&swap)==1;n++) {}
	fclose(file);
	return n;
}

float* MyData::readData(const char* filename){
	FILE* file;
	float* dataArray;
	
	dataArray = (float*) malloc(_ndati * sizeof(float));
	file = myfopen(filename);
	for(unsigned int i=0;i<_ndati;i++){
		fscanf(file,"%f",&dataArray[i]);
	}
	fclose(file);
	return dataArray;
}

//public methods

unsigned int MyData::getSize(void){
	return _ndati;
}

unsigned int MyData::getOrigSize(void){
	return _ndatiOrig;
}

float* MyData::getData(void){
	return _data;
}

float* MyData::getOrigData(void){
	return _dataOrig;
}

void MyData::removeFirstData(unsigned int num){ // removes first num data from array
	if(num >= _ndati){
		fprintf(stderr, "\nError: Could not remove first %d data.\n", num);
		return;
	}
	float *newData;
	newData = (float *) malloc((_ndati - num)*sizeof(float));
	_ndati = _ndati - num;
	newData = (float *) memcpy((void *)newData, (void *)(_data+num),_ndati * sizeof(float));
	free((void *)_data);
	_data = newData;
}

void MyData::removeData(unsigned int index){ // removes data in the given position (0<=index<ndata)
	if(index >= _ndati){
		fprintf(stderr, "\nError: Could not remove data in position %d.\n", index);
		return;
	}
	float *temp, *newData;
	newData = (float *) malloc((_ndati - 1) * sizeof(float));
	temp = (float *) malloc((_ndati - index -1) * sizeof(float));
	newData = (float *) memcpy((void *)newData, (void *)_data, index*sizeof(float));
	temp = newData + index;
	temp = (float *) memcpy((void *)temp, (void *)(_data+index+1), (_ndati-index-1)*sizeof(float));
	free((void *)_data);
	_data = newData;
	_ndati--;
}

void MyData::removeLastData(unsigned int num){ // removes last num data from array
	if(num >= _ndati){
		fprintf(stderr, "\nError: Could not remove last %d data.\n", num);
		return;
	}
	float *newData;
	_ndati = _ndati - num;
	newData = (float *) malloc(_ndati * sizeof(float));
	newData = (float *) memcpy((void *)newData, (void *)_data, _ndati * sizeof(float));
	free((void *)_data);
	_data = newData;
}

void MyData::printData(void){
	printf("\n\n Data:\n");
	for(uint i=0;i<_ndati;i++)
		printf("%f\n", _data[i]);
	printf("\n\n");
}

void MyData::printData(int index){
	printf("\n\n Data %d: %f\n\n", index, _data[index]);
}

void MyData::printOrigData(void){
	printf("\n\n Original Data:\n");
	for(uint i=0;i<_ndatiOrig;i++)
		printf("%f\n", _dataOrig[i]);
	printf("\n\n");
}

void MyData::printOrigData(int index){
	printf("\n\n Original Data %d: %f\n\n", index, _dataOrig[index]);
}

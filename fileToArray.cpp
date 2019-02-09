#include "fileToArray.h"

MyData::MyData(const char* filename){
	_ndati = countData(filename);
	_data = readData(filename);
}

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

int MyData::countData(const char* filename){
	FILE* file;
	int n;
	float swap;
	
	file = myfopen(filename);
	for(n=0;fscanf("%f",&swap)==1;n++) {}
	fclose(file);
	return n;
}

float* MyData::readData(const char* filename){
	FILE* file;
	float* dataArray;
	
	dataArray = (float*) malloc(_ndati * sizeof(float));
	file = myfopen(filename);
	for(int i=0;i<_ndati;i++){
		fscanf(file,"%f",&dataArray[i]);
	}
	fclose(file);
	return dataArray;
}

int MyData::getSize(void){
	return _ndati;
}

float* MyData::getData(){
	return _data;
}

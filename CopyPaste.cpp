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
	int getSize(void){
		return _ndati;
	}
	float* getData(void){
		return _data;
	}
	// attributes
	
	// constructor
	MyData(const char* filename){
		_ndati = countData(filename);
		_data = readData(filename);
	}
	private:
	// methods
	FILE* myfopen(const char* filename){
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
	int countData(const char* filename){
		FILE* file;
		int n;
		float swap;
		
		file = myfopen(filename);
		for(n=0;fscanf("%f",&swap)==1;n++) {}
		fclose(file);
		return n;
	}
	float* readData(const char* filename){
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
	// attributes
	int _ndati;
	float* _data;
};

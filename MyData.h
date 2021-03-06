/* MyData.h
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

#ifndef MYDATA_H
#define MYDATA_H

#include <cstdio>
#include <cstdlib>

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
	
//	ClassDef(MyData, 0);
};

#endif

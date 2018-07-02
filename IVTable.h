/*
 * IVTable.h
 *
 *  Created on: Jun 11, 2018
 *      Author: OS1
 */

#ifndef H_IVTABLE_H_
#define H_IVTABLE_H_

#include "Def.h"

class IVTEntry;

class IVTable {
public:

	IVTEntry *entries[256];

	IVTable() {
		int i = 0;
		for (; i < 256; i++) {
			entries[i] = NULL;
		}
	}

	~IVTable() {
		int i = 0;
		for (; i < 256; i++) {
			entries[i] = NULL;
		}

		delete[] entries;
	}
	static IVTable *myInterruptVectorTable;

};

#endif /* H_IVTABLE_H_ */

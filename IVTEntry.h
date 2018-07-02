/*
 * IVTEntry.h
 *
 *  Created on: Jun 3, 2018
 *      Author: OS1
 */

#ifndef H_IVTENTRY_H_
#define H_IVTENTRY_H_
#include "Def.h"
#include <DOS.H>

class KernelEvent;

class IVTEntry {
public:
	IVTEntry(int id, pInterrupt newRoutine);
	~IVTEntry();

	//methods
	void callOldRoutine();
	void restoreOldRoutine();
	void signal();
	void setEvent(KernelEvent *myEvent) {
		this->myEvent = myEvent;
	}

	int id;
	pInterrupt oldRoutine;
	KernelEvent *myEvent;
};

#endif /* H_IVTENTRY_H_ */

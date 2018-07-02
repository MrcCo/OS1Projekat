/*
 * KSem.cpp
 *
 *  Created on: May 24, 2018
 *      Author: OS1
 */

#include "KSem.h"
#include "Def.h"
#include "PCBList.h"
#include "PCB.h"
#include "Thread.h"
#include "SCHEDULE.h"

//constructor
KernelSem::KernelSem(int init) {
	this->val = init;
	if (waitingList != NULL) {
		waitingList = new PCBList();
	}
	lck = 0;
}

//destructor
KernelSem::~KernelSem(){
	delete waitingList;
}


/********************************/
/*		Methods					*/
int KernelSem::wait(int toBlock) {
	semLock();
	if (toBlock <= 0) {
		if (val > 0) {
			val--;
			semUnlock();
			return 0;
		} else {
			semUnlock();
			return -1;
		}
	} else {
		val--;
		if (val < 0) {
			PCB::running->state = BLOCKED;
			waitingList->insertFirst((PCB*) PCB::running);
			semUnlock();
			dispatch();
			return 1;
		} else {
			semUnlock();
			return 0;
		}
	}
	semUnlock();
}

void KernelSem::signal() {
	semLock();
	val++;
	if (val <= 0) {
		PCB* temp = waitingList->getFirst();
		temp->state = READY;
		Scheduler::put (temp);
	}
	semUnlock();

}

int test_and_set(int x) {

	if (x) {
		return 1;
	} else {
		x = 1;
		return 0;
	}

}

void KernelSem::semLock() {
	while (test_and_set(KernelSem::lck))
		;
}

void KernelSem::semUnlock() {
	KernelSem::lck = 0;
}


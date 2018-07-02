/*
 * KSem.h
 *
 *  Created on: May 24, 2018
 *      Author: OS1
 */

#ifndef H_KSEM_H_
#define H_KSEM_H_

class PCBList;

class KernelSem {
public:
	//constructor
	KernelSem(int init);

	//destructor
	~KernelSem();

	//methods
	int wait(int toBlock);
	void signal();
	int getVal() const { return val; }

	void semLock();
	void semUnlock();

	volatile int val;
	PCBList *waitingList;
	int lck;
};

#endif /* H_KSEM_H_ */

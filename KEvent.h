/*
 * KEvent.h
 *
 *  Created on: Jun 3, 2018
 *      Author: OS1
 */

#ifndef H_KEVENT_H_
#define H_KEVENT_H_

#include "Def.h"

class PCB;

class KernelEvent{
public:

	KernelEvent(IVTNo ivtNo);
	~KernelEvent();

	void wait();
	void signal();


	PCB* myPCB;
	IVTNo ivtNo;
	volatile int val;


	void block();
	void deblock();
};


#endif /* H_KEVENT_H_ */

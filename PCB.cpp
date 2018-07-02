/*
 * PCB.cpp
 *
 *  Created on: May 22, 2018
 *      Author: OS1
 */

/*
 * PCB.cpp
 *
 *  Created on: May 19, 2018
 *      Author: OS1
 */
#include "Thread.h"
#include "PCB.h"
#include "Def.h"
#include "SCHEDULE.h"
#include "PCBList.h"
#include "W8List.h"
#include "IdleT.h"
#include "SlpList.h"
//this include is confusing bcs i had to remove defaultStackSize and defaultTimeSlice from Thread.h
#include "Thread.h"

#include <DOS.H>
#include <STDIO.H>

int PCB::ID = 0;
PCB* PCB::running = NULL;
//PCB* PCB::mainPCB = NULL;
/*********************************/
/*		Constructor				 */

PCB::PCB(Thread *Thread, unsigned long stackSize, unsigned int timeSlice) {

	if (stackSize > 65535) {
		stackSize = 65534;
	}
		//setting up Thread's stack

		stackSize /= sizeof(unsigned);
		stack = new unsigned[stackSize];

#ifndef BCC_BLOCK_IGNORE
		//setting up the parameter of the wrapper function
		//stack[stackSize - 1] = FP_SEG(myThread);
		//stack[stackSize - 2] = FP_OFF(myThread);

		//setting up PSW register, and enabling the I bit
		stack[stackSize - 1] = 0x200;

		//setting up PC -> CS i IP
		stack[stackSize - 2] = FP_SEG(PCB::wrapper);
		stack[stackSize - 3] = FP_OFF(PCB::wrapper);

		//setting up SS, SP, BP
		ss = FP_SEG(stack + stackSize - 12);
		sp = FP_OFF(stack + stackSize - 12);
		bp = sp;
#endif

		//setting up timeSlice
		this->timeSlice = timeSlice;
		this->timeToSleep = 0;

		//setting up state
		state = NEW;

		//setting up myThread
		myThread = Thread;

		//setting up wait queue
		waitingQueue = new WaitList();


		PCBList::pcbList->insertFirst(this);

		pcbID = ++ID;
		//printf("My id is:%d\n",id);
}

PCB::~PCB(){

	delete[] stack;

}

/*********************************/
/*		Methods					 */

//Thread controling methods

void PCB::waitToComplete(){

		if (PCB::running == this || state == FINISHED || myThread == IdleThread::idleThread) {
			// Thread can't wait on itself, doesn't need to wait on a completed thread, and shouldn't wait on the idle thread

			return;
		}
		PCB::running->state = BLOCKED;
		waitingQueue->insertFirst(running);

		dispatch();

}

void PCB::start(){
#ifndef BCC_BLOCK_IGNORE
	lock();

	if(state == NEW){

		state = READY;
		Scheduler::put(this);

	}

	unlock();
#endif
}

void PCB::sleep(unsigned int timeToSleep){
#ifndef BCC_BLOCK_IGNORE


	//printf("Test in sleep: %d\n", running->getID());

	if(timeToSleep > 0){

		PCB::running->state = BLOCKED;
		PCB::running->timeToSleep = timeToSleep;
		SleepList::sleepingThreads->insertSorted(PCB::running);

	}

	dispatch();

#endif
}

int PCB::getID(){
	return pcbID;
}

//wrapper
void PCB::wrapper(){

#ifndef BCC_BLOCK_IGNORE

	PCB::running->myThread->run();
	PCB::running->state = FINISHED;
	if(PCB::running->waitingQueue->first){
		PCB::running->waitingQueue->wakeUp();
	}

	dispatch();
#endif
}

/*********************************/





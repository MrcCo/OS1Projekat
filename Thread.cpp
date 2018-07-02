/*
 * Thread.cpp
 *
 *  Created on: May 22, 2018
 *      Author: OS1
 */

/*********************************/
/*		Includes 				 */

#include "Thread.h"
#include "PCB.h"
#include "Def.h"
#include "Timer.h"
#include "STDIO.H"
/*********************************/
/*		Constructor				 */

Thread::Thread(StackSize stackSize, Time timeSlice) {

	myPCB = new PCB(this, stackSize, timeSlice);
	//printf("Finished Thread const\n");
}

/*********************************/
/*		Destructor				 */

Thread::~Thread() {

	waitToComplete();
	delete myPCB;

}


/*********************************/
/*		Methods					 */

void Thread::start() {
	myPCB->start();
}

void Thread::waitToComplete() {
	myPCB->waitToComplete();
}

void Thread::sleep(Time timeToSleep) {
	PCB::sleep((unsigned long) timeToSleep);
}

int Thread::getId() const {
	return myPCB->getID();
}
int Thread::contextSwitchRequested = 0;

void dispatch() {

	Thread::contextSwitchRequested = 1;
	asm int 8h;
}


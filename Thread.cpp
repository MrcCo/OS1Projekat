/*
 * Thread.cpp
 *
 *  Created on: May 22, 2018
 *      Author: OS1
 */


#include "Thread.h"
#include "PCB.h"
#include "Def.h"
#include "Timer.h"
#include "STDIO.H"

//constructor
//just creates Thread's PCB
Thread::Thread(StackSize stackSize, Time timeSlice) {

	myPCB = new PCB(this, stackSize, timeSlice);

}

//destructor
//calls waitToComplete method and deletes the PCB
Thread::~Thread() {

	waitToComplete();
	delete myPCB;

}


//thread control methods
//just wrapper methods calling PCB methods
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


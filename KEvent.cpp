/*
 * KEvent.cpp
 *
 *  Created on: Jun 3, 2018
 *      Author: OS1
 */
#include "KEvent.h"
#include "PCB.h"
#include "Thread.h"
#include "SCHEDULE.h"
#include "IVTable.h"
#include "Def.h"
#include "IVTEntry.h"

//constructor
//connects running PCB to the event, and inserts the event in the IVTable
KernelEvent::KernelEvent(IVTNo ivtNo){

	myPCB = PCB::running;
	IVTable::myInterruptVectorTable->entries[(int) ivtNo]->setEvent(this);

}

//destructor
KernelEvent::~KernelEvent(){

	IVTable::myInterruptVectorTable->entries[(int) ivtNo]->restoreOldRoutine();
	IVTable::myInterruptVectorTable->entries[(int) ivtNo] = NULL;

}

//standard wait method
void KernelEvent::wait(){

	if(myPCB == PCB::running && val-- == 0){
		block();
	}

}

//standard signal method
void KernelEvent::signal(){

	if(val<1 && val++<0){
		deblock();
	}

}

//blocks the running thread and initiates context switch
void KernelEvent::block() {

	if(myPCB != NULL){
		myPCB->state = BLOCKED;
	}
	dispatch();

}

//deblocks the thread and returns it to the scheduler
void KernelEvent::deblock() {
	
	myPCB->state = READY;
	Scheduler::put(myPCB);
	
}


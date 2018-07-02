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

KernelEvent::KernelEvent(IVTNo ivtNo){

	//lock

	myPCB = PCB::running;
	IVTable::myInterruptVectorTable->entries[(int) ivtNo]->setEvent(this);

	//unlock


}

KernelEvent::~KernelEvent(){

	IVTable::myInterruptVectorTable->entries[(int) ivtNo]->restoreOldRoutine();
	IVTable::myInterruptVectorTable->entries[(int) ivtNo] = NULL;

}


void KernelEvent::wait(){

	//lock

	if(myPCB == PCB::running && val-- == 0){
		block();
	}

	//unlock

}

void KernelEvent::signal(){

	//lock


	if(val<1 && val++<0){
		deblock();
	}

	//unlock
}

void KernelEvent::block() {

	//lock

		if(myPCB != NULL){
			myPCB->state = BLOCKED;
		}
		dispatch();

	//unlock
}

void KernelEvent::deblock() {

	//lock
		myPCB->state = READY;
		Scheduler::put(myPCB);
	//unlock
}


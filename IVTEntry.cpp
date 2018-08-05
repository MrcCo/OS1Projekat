/*
 * IVTEntry.cpp
 *
 *  Created on: Jun 3, 2018
 *      Author: OS1
 */

#include "IVTEntry.h"
#include "KEvent.h"
#include "IVTable.h"
#include "DOS.h"
#include "Def.h"

//constructor
//sets up a new interrupt routine, and adds it to the IVTable
IVTEntry::IVTEntry(int id, pInterrupt newRoutine) {
	if (id < 256) {
		this->id = id;

#ifndef BCC_BLOCK_IGNORE
		oldRoutine = getvect(id);
		setvect(id, newRoutine);
		IVTable::myInterruptVectorTable->entries[id] = this;
#endif
	}
}

//destrucotr
IVTEntry::~IVTEntry() {
	IVTable::myInterruptVectorTable->entries[id] = NULL;
	restoreOldRoutine();
}

//calls old routine
void IVTEntry::callOldRoutine() {
	if (oldRoutine != NULL)
		oldRoutine();
}

//standard signal method
void IVTEntry::signal() {
	if (myEvent != NULL) {
		myEvent->signal();
	}
}

//this method restores old routine 
void IVTEntry::restoreOldRoutine() {
#ifndef BCC_BLOCK_IGNORE
	if(oldRoutine!=NULL) {
		setvect(id, oldRoutine);
		oldRoutine = NULL;
	}
#endif
}

/*
 * Timer.cpp
 *
 *  Created on: May 23, 2018
 *      Author: OS1
 */

#include "Timer.h"
#include "SCHEDULE.h"
#include "PCB.h"
#include "Def.h"
#include "PCBList.h"
#include "SlpList.h"
#include "W8List.h"
#include "Thread.h"
#include "IdleT.h"
#include <STDIO.H>



pInterrupt oldIR;

void inic() {

#ifndef BCC_BLOCK_IGNORE

	asm pushf;
	asm cli;

	oldIR = getvect(0x8);
	setvect(0x8, timer);
	setvect(0x60, oldIR);

	//printf("Finished inic");

	asm popf;

#endif

}

void restore() {
#ifndef BCC_BLOCK_IGNORE
	asm pushf;
	asm cli;

	setvect(0x8, oldIR);

	//printf("Finished restore");
	asm popf;
#endif
}

volatile unsigned tss, tsp, tbp;
volatile int counter = 20;
volatile int contextSwitchRequested = 0;

//necessary variables for context switch

void tick();
//up to the user to define it !

void interrupt timer(...) {

	if (counter == 0 || Thread::contextSwitchRequested) {
#ifndef BCC_BLOCK_IGNORE
		asm {
			mov tss, ss;
			mov tsp, sp;
			mov tbp, bp;
		};
#endif

		PCB::running->ss = tss;
		PCB::running->sp = tsp;
		PCB::running->bp = tbp;

		//printf("Context switching \n");
		//printf("IDS: %d %d\n", PCB::running->getID(), IdleThread::idleThread->getId());

		//DO NOT PUT IDLE IN SCHEDULER
		if (PCB::running != NULL) {
			if (PCB::running->state == RUNNING
					&& PCB::running->myThread
							!= (Thread*) IdleThread::idleThread) {

				PCB::running->state = READY;
				//printf("U scheduler stavljam %d pcb\n", PCB::running->id);
				Scheduler::put(PCB::running);

			}
		}
		//printf("Spremam se da uzmem\n");
		PCB::running = Scheduler::get();
		//printf("Uzeo\n");
		if (PCB::running == 0) {
			//printf("No more threads left in scheduler");
			PCB::running = IdleThread::idleThread->getPCB();
		}
		//printf("Iz scheduler uzimam %d pcb\n", PCB::running->id);
		PCB::running->state = RUNNING;

		tsp = PCB::running->sp;
		tss = PCB::running->ss;
		tbp = PCB::running->bp;

		counter = PCB::running->timeSlice;

#ifndef BCC_BLOCK_IGNORE
		asm {
			mov bp, tbp
			mov ss, tss
			mov sp, tsp
		}
#endif

	}


	if (!Thread::contextSwitchRequested) {
		//printf("ContextSwitch isnt requested \n");
		counter--;
		tick();
		oldIR();
		if (SleepList::sleepingThreads->first != 0) {

				SleepList::sleepingThreads->simulateSleep();

		}
	}

	Thread::contextSwitchRequested = 0;

}

/*

 /**************************************************/
/*
 unsigned oldTimerOFF, oldTimerSEG;

 // postavlja novu prekidnu rutinu
 void Timer::inic(){
 #ifndef BCC_BLOCK_IGNORE
 asm{
 cli
 push es
 push ax

 mov ax,0
 mov es,ax

 mov ax, word ptr es:0022h
 mov word ptr oldTimerSEG, ax
 mov ax, word ptr es:0020h
 mov word ptr oldTImerOFF, ax

 mov word ptr es:0x0022h, seg timer
 mov word ptr es:0x0020h, offset timer

 mov ax, oldTimerSEG
 mov word ptr es:0182h, ax
 mov ax, oldTimerOFF
 mov word ptr es:0180h, ax

 pop ax
 pop es

 sti
 }

 #endif
 }

 vraca staru prekidnu rutinu
 void Timer::restore(){
 #ifndef BCC_BLOCK_IGNORE
 asm {
 cli
 push es
 push ax

 mov ax,0
 mov es,ax


 mov ax, word ptr oldTimerSEG
 mov word ptr es:0022h, ax
 mov ax, word ptr oldTimerOFF
 mov word ptr es:0020h, ax

 pop ax
 pop es
 sti
 }
 #endif
 }
 */


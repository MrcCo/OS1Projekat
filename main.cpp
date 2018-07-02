// File: main.cpp
#include <iostream.h>
#include <stdlib.h>
#include "PCB.h"
#include "Thread.h"
#include "Timer.h"
#include "MainT.h"
#include "IdleT.h"
#include "Def.h"

int main(int argc, char *argv[]) {

	printf(" Hello people\n");


	PCB *mainPcb = new PCB(NULL, 0, 1);
	mainPcb->state = RUNNING;
	PCB::running = mainPcb;

	// Set the arguments for the user main thread:
	MainThread::mainThread->setArgs(argc, argv);

	//redosled kojim dodajem argumente u cmd line
	//velicina_bafera br_niti time_slice

	// Put the user main thread in the scheduler:
	MainThread::mainThread->start();
	inic();

	// Wait for the user main thread to complete, and then delete it:
	delete MainThread::mainThread;

	restore();

	int ret =  MainThread::retVaule;

	// Delete the Kernel threads, and the Kernel itself:
	delete mainPcb;
	delete IdleThread::idleThread;

	printf("\n Bye people \n");

	return ret;
}

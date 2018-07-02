/*
 * PCB.h
 *
 *  Created on: May 22, 2018
 *      Author: OS1
 */

#ifndef H_PCB_H_
#define H_PCB_H_

class Thread;
class WaitList;

class PCB{
public:
	friend class Thread;

	//constructor
	PCB(Thread *myThread, unsigned long stackSize = 4096, unsigned int timeSlice = 2);

	//destructor
	~PCB();

	//Thread controling methods
	void waitToComplete();
	void start();
	static void sleep(unsigned int timeToSleep);

	//wrapper
	static void wrapper();

	int getID();


	//stack defining atributes
	unsigned *stack;
	volatile unsigned ss;
	volatile unsigned sp;
	volatile unsigned bp;

	//depicts the state of the thread
	volatile short state;

	//points at the thread this pcb represents
	Thread *myThread;

	//time values
	unsigned int timeSlice;
	unsigned int timeToSleep;


	//queue of threads that wait for this one to complete
	WaitList *waitingQueue;

	//pcb id
	static int ID;
	int pcbID;

	static PCB* running;
};



#endif /* H_PCB_H_ */

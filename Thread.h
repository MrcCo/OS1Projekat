/*
 * Thread.h
 *
 *  Created on: May 22, 2018
 *      Author: Marko
 */

#ifndef H_THREAD_H_
#define H_THREAD_H_

typedef unsigned Time;
static Time defaultTimeSlice = 2;

typedef unsigned long StackSize;
static StackSize defaultStackSize = 4096;
#include <STDIO.H>

class PCB;

class Thread {
public:
	void start();
	void waitToComplete();
	virtual ~Thread();
	static void sleep(Time timeToSleep);
	int getId() const;
	PCB* getPCB() const{
		return myPCB;
	}
	static int contextSwitchRequested;
	Thread(StackSize stackSize = defaultStackSize, Time timeSlice = defaultTimeSlice);

protected:
	friend class PCB;
	virtual void run(){}

private:
	PCB* myPCB;

};

void dispatch();





#endif /* H_THREAD_H_ */

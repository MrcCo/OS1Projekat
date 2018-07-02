/*
 * Sem.h
 *
 *  Created on: May 24, 2018
 *      Author: OS1
 */

#ifndef H_SEM_H_
#define H_SEM_H_

class KernelSem;

class Semaphore {

public:
	Semaphore (int init=1);
	virtual ~Semaphore ();
	virtual int wait (int toBlock);
	virtual void signal();
	int val () const; // Returns the current value of the semaphore
private:
	KernelSem* myImpl;
};


#endif /* H_SEM_H_ */

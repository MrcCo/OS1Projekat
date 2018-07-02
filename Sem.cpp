/*
 * Sem.cpp
 *
 *  Created on: May 24, 2018
 *      Author: OS1
 */

#include "KSem.h"
#include "Sem.h"
#include "Def.h"
Semaphore::Semaphore(int init) {
	myImpl = new KernelSem(init);
}

Semaphore::~Semaphore() {
	delete myImpl;
}

int Semaphore::wait(int toBlock) {

	return (myImpl->wait(toBlock));

}

void Semaphore::signal() {

	myImpl->signal();

}

int Semaphore::val() const {
	return myImpl->getVal();
}


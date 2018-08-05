/*
 * Event.cpp
 *
 *  Created on: Jun 3, 2018
 *      Author: OS1
 */
#include "Event.h"
#include "KEvent.h"

//constructor
//just creates a kernel event
Event::Event(IVTNo ivtNo) {
	lock();
	myImpl = new KernelEvent(ivtNo);
	unlock();
}

//destructor
Event::~Event() {
	delete myImpl;
}

//methods
void Event::wait() {
	lock();
	myImpl->KernelEvent::wait();
	unlock();
}

void Event::signal() {
	lock();
	myImpl->signal();
	unlock();
}


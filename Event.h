/*
 * Event.h
 *
 *  Created on: Jun 3, 2018
 *      Author: OS1
 */

#ifndef H_EVENT_H_
#define H_EVENT_H_

#include "Def.h"
#include "IVTEntry.h"
#include "KEvent.h"
class KernelEvent;


#define PREPAREENTRY(numEntry, callOld) \
void interrupt inter##numEntry(...); \
IVTEntry newEntry##numEntry(numEntry, inter##numEntry); \
void interrupt inter##numEntry(...) { \
	if (callOld == 1) \
		newEntry##numEntry.callOldRoutine(); \
	newEntry##numEntry.signal(); \
	dispatch(); \
}


class Event {
public:
	Event(IVTNo ivtNo);
	~Event();
	void wait();
protected:
	friend class KernelEvent;
	void signal(); // can call KernelEv
private:
	KernelEvent* myImpl;
};









#endif /* H_EVENT_H_ */

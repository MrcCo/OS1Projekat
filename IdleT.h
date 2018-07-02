/*
 * IdleT.h
 *
 *  Created on: May 22, 2018
 *      Author: OS1
 */

#ifndef H_IDLET_H_
#define H_IDLET_H_

#include "Thread.h"

/*********************************/
/*		Class IdleThread		 */
class IdleThread: public Thread {
public:
	IdleThread() :	Thread(0,1) {};

	~IdleThread() {}

	virtual void run() {
		while (1);
	}

	static IdleThread *idleThread;
};



#endif /* H_IDLET_H_ */

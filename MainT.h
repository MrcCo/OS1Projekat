/*
 * MainT.h
 *
 *  Created on: May 22, 2018
 *      Author: OS1
 */

#ifndef H_MAINT_H_
#define H_MAINT_H_
#include "Thread.h"

class MainThread: public Thread {

public:

	static int argc;
	static char** argv;
	static int retVaule;

	//constructor
	MainThread(){};
	~MainThread() { waitToComplete(); }

	//methods
	static void setArgs(int ARGC, char** ARGV);
	virtual void run();

	//static instance
	static MainThread* mainThread;
};






#endif /* H_MAINT_H_ */

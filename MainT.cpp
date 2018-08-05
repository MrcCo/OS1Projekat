/*
 * MainT.cpp
 *
 *  Created on: May 22, 2018
 *      Author: OS1
 */
#include "MainT.h"

//initialising static (global) variables
MainThread* MainThread::mainThread = new MainThread();
int MainThread::argc = 0;
int MainThread::retVaule = 0;
char** MainThread::argv = 0;

//provided by some online tests
int syncPrintf(const char *format, ...);

//sets arguments for userMain method
void MainThread::setArgs(int ARGC, char** ARGV) {
	argc = ARGC;
	argv = ARGV;
}

extern int userMain (int argc, char* argv[]);

//run method just needs to call userMain and set the return value 
void MainThread::run() {
	MainThread::retVaule = userMain(argc, argv);
}


/*
 * MainT.cpp
 *
 *  Created on: May 22, 2018
 *      Author: OS1
 */
#include "MainT.h"
/*********************************/
/*		Class MainThread         */
MainThread* MainThread::mainThread = new MainThread();
int MainThread::argc = 0;
int MainThread::retVaule = 0;
char** MainThread::argv = 0;
int syncPrintf(const char *format, ...);

void MainThread::setArgs(int ARGC, char** ARGV) {
	argc = ARGC;
	argv = ARGV;
}

extern int userMain (int argc, char* argv[]);

void MainThread::run() {
	MainThread::retVaule = userMain(argc, argv);
}


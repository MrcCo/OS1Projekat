/*
 * Def.h
 *
 *  Created on: May 22, 2018
 *      Author: OS1
 */

#ifndef H_DEF_H_
#define H_DEF_H_

//state definitions
#define NEW 0
#define READY 1
#define RUNNING 2
#define BLOCKED 3
#define FINISHED 4

//null ptr defintion
#define NULL 0

//lock and unlock
#define lock() asm { pushf; cli; }

#define unlock() asm popf

typedef void interrupt (*pInterrupt)(...);
typedef unsigned char IVTNo;

#endif /* H_DEF_H_ */

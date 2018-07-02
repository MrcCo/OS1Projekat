/*
 * SlpList.h
 *
 *  Created on: May 22, 2018
 *      Author: OS1
 */

#ifndef H_SLPLIST_H_
#define H_SLPLIST_H_



class PCB;

class SleepList{
public:
	struct Node{

		PCB* pcb;
		Node *next;


		Node(PCB *p, Node *ne = 0):pcb(p),next(ne){};

	};


	//constructor
	SleepList();

	//destructor
	~SleepList();

	//standard array methods
	void insertFirst(PCB *newPCB);
	void insertLast(PCB *newPCB);
	void insertSorted(PCB *newPCB);


	//methods for sleeping list
	void decrementAll(int dec = 1);
	void simulateSleep();


	Node *first,*last;
	static SleepList *sleepingThreads;
};



#endif /* H_SLPLIST_H_ */

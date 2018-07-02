/*
 * W8List.h
 *
 *  Created on: May 22, 2018
 *      Author: OS1
 */

#ifndef H_W8LIST_H_
#define H_W8LIST_H_

class PCB;

class WaitList {
public:
	struct Node{

		PCB* pcb;
		Node *next;

		Node(PCB *p, Node *ne = 0):pcb(p),next(ne){};

	};

	//constructor
	WaitList();

	//destructor
	~WaitList();

	//standard array methods
	void insertFirst(PCB *newPCB);
	PCB* getFirst();
	void wakeUp();


	Node *first,*last;

};


#endif /* H_W8LIST_H_ */

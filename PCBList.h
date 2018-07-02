/*
 * PCBList.h
 *
 *  Created on: May 22, 2018
 *      Author: OS1
 */

#ifndef H_PCBLIST_H_
#define H_PCBLIST_H_

	/************************************************/
	/*			Forward Declaration					*/
	class PCB;

class PCBList {
public:
	/************************************************/
	/*				Node							*/
	struct Node{

		PCB* pcb;
		Node *next;

		Node(PCB *p, Node *ne = 0):pcb(p),next(ne){};

	};


	//constructor
	PCBList();

	//destructor
	~PCBList();

	//standard array methods
	void insertFirst(PCB *newPCB);
	void insertLast(PCB *newPCB);

	PCB* getFirst();

	/************************************************/
	/*				Atrubutes						*/

	Node *first,*last;

	/************************************************/
	static PCBList* pcbList;
};

//List of all PCB's


#endif /* H_PCBLIST_H_ */

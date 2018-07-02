/*
 * W8List.cpp
 *
 *  Created on: May 22, 2018
 *      Author: OS1
 */
#include "W8List.h"
#include "PCB.h"
#include "Def.h"
#include "SCHEDULE.h"
#include <STDIO.H>

//constructor
WaitList::WaitList() {
	first = NULL;
	last = NULL;
}

//destructor
WaitList::~WaitList(){
	Node* currentNode = this->first; // initialize current node to first
	while (currentNode){

		Node* nextNode = currentNode->next;    // get next node
		delete currentNode;                         // delete current
		currentNode = nextNode;                     // set current to "old" next

	}
	this->first = NULL;
	this->last = NULL;
}


void WaitList::insertFirst(PCB *newPCB) {

	if (newPCB != NULL) {
		if (first == 0) {
			first = new Node(newPCB);
			last = first;
			return;
		}

		Node *temp = new Node(newPCB);
		temp->next = first;
		first = temp;
	}
	return;

}

//most likely useless


void WaitList::wakeUp() {


	Node* currentNode = this->first; // initialize current node to first
	while (currentNode){

		Node* nextNode = currentNode->next;    // get next node
		Scheduler::put(currentNode->pcb);
		delete currentNode;                         // delete current
		currentNode = nextNode;                     // set current to "old" next

	}
	this->first = NULL;
	this->last = NULL;


}


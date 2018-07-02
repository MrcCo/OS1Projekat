/*
 * PCBList.cpp
 *
 *  Created on: May 22, 2018
 *      Author: OS1
 */

#include "PCBList.h"
#include "PCB.h"
#include "Def.h"
#include "stdio.h"
PCBList* PCBList::pcbList = new PCBList();

//constructor
PCBList::PCBList() {
	first = NULL;
	last = NULL;
}

PCBList::~PCBList(){
	Node* currentNode = this->first; // initialize current node to first
	while (currentNode){

		Node* nextNode = currentNode->next;    // get next node
		delete currentNode;                         // delete current
		currentNode = nextNode;                     // set current to "old" next

	}
	this->first = NULL;
	this->last = NULL;
}

/************************************************/
/*				Methods							*/

void PCBList::insertFirst(PCB *newPCB) {

	if (newPCB) {
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

void PCBList::insertLast(PCB *newPCB) {

	if (newPCB) {
		if (last == NULL) {
			last = new Node(newPCB);
			first = last;
			return;
		}

		Node *temp = new Node(newPCB);
		last->next = temp;
		last = temp;
	}
		return;

}


PCB* PCBList::getFirst() {

	Node* firstNode = first;
	if (first != NULL)
		first = first->next;
	PCB* temp = NULL;
	if (firstNode != NULL) {

		temp = firstNode->pcb;
		delete firstNode;

	}
	if(first == NULL){
		last == NULL;
	}
	return temp;
}


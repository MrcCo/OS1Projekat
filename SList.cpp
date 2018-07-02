#include "SlpList.h"
#include "PCB.h"
#include <STDIO.H>
#include "SCHEDULE.H"
#include "Def.h"
#include "IdleT.h"
SleepList* SleepList::sleepingThreads = new SleepList();

//konstruktor
SleepList::SleepList() {
	first = last = 0;
}

SleepList::~SleepList(){
	Node* currentNode = this->first; // initialize current node to first
	while (currentNode){

		Node* nextNode = currentNode->next;    // get next node
		delete currentNode;                         // delete current
		currentNode = nextNode;                     // set current to "old" next

	}
	this->first = NULL;
	this->last = NULL;
}

void SleepList::insertFirst(PCB *newPCB) {

	if (newPCB) {
		if (first == 0) {
			first = new Node(newPCB);
			last = first;
			return;
		}

		Node* temp = new Node(newPCB);
		temp->next = first;
		first = temp;

	}

}

void SleepList::insertLast(PCB *newPCB) {

	if (newPCB != 0) {

		if (first == 0) {
			first  = new Node(newPCB);
			last = first;
			return;
		} else {
			Node *prev = last;
			last = last->next = new Node(newPCB);

		}
	}
}

void SleepList::insertSorted(PCB *newPCB) {

	//exception
	if (newPCB == 0) {
		return;
	}

	Node *temp = new Node(newPCB);

	//exception
	if (temp == 0){
		return;
	}
	if (first == NULL) {
		first = temp;
		last = temp;
		return;
	}

	//if sleep time is smaller then first's then put it at the start
	if (temp->pcb->timeToSleep <= first->pcb->timeToSleep) {
		temp->next = first;
		first = temp;
		//printf("Novi first je: %d", first->pcb->id);
		return;
	}

	//if its greater put int at the end
	if (temp->pcb->timeToSleep >= last->pcb->timeToSleep) {
		last = last->next = temp;
		//printf("Novi last je: %d", last->pcb->id);
		return;
	}

	//put it in so the list remains sorted
	Node * curr = first;
	Node * prev = 0;

	//curr is the first element greater thn
	while (curr != 0 && curr->pcb->timeToSleep < temp->pcb->timeToSleep) {
		prev = curr;
		curr = curr->next;
	}

	if (!prev) {
		//error
		return;
	}
	if (!curr) {
		//error
		return;
	}

	prev->next = temp;
	temp->next = curr;

	return;

}

void SleepList::decrementAll(int dec) {


	Node *temp = first;

	while (temp != 0) {
		//printf("Originalni time to sleep %d niti %d" , temp->pcb->timeToSleep, temp->pcb->id);
		temp->pcb->timeToSleep -= dec;
		//printf("Novi time to sleep %d %d \n", temp->pcb->timeToSleep, temp->pcb->id);
		temp = temp->next;

	}

}

void SleepList::simulateSleep() {

	//lock();
	if (first == 0)
		return;
	//printf("Im here %d\n", first->pcb->timeToSleep);
	decrementAll();

	while (first != 0 && first->pcb->timeToSleep == 0) {
		//here we update the thread's state, put it in the scheduler and then update the first node
		//printf("Suddenly im here %d", first->pcb->timeToSleep);

		Node *temp = first;
		first = first->next;

		PCB* wakeUp = temp->pcb;
		wakeUp->state = READY;
		Scheduler::put(wakeUp);
		delete temp;

	}


	//unlock();
}

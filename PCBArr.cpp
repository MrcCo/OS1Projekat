/*
 * PCBArr.cpp
 *
 *  Created on: Jun 15, 2018
 *      Author: OS1
 */
#include "PCBArr.h"
#include "Def.h"
#include "PCB.h"
//static gloabal array
PCBArray* PCBArray::allPCBs = new PCBArray();

//constructor
PCBArray::PCBArray(int cap) {

	this->cap = cap;
	array = new PCB*[this->cap];
	last = 0;

	int i;
	for (i = 0; i < cap; i++) {
		array[i] = NULL;
	}

}

//destructor
PCBArray::~PCBArray() {

	int i;
	for (i = 0; i < cap; i++) {
		array[i] = NULL;
	}

	delete[] array;
}

//methods
void PCBArray::addPCB(PCB* newPcb) {

	if (last < cap) {
		newPcb->pcbID = last;
		array[last++] = newPcb;
	}

}

PCB* PCBArray::getPCB(int i){

	if (i >= 0 && i < last) {
		return array[i];
	}
	return NULL;

}

void PCBArray::removePCB(int i) {

	if (i >= 0 && i < last) {
		array[i] = NULL;
	}

}


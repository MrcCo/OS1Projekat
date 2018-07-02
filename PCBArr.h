/*
 * PCBArray.h
 *
 *  Created on: Jun 15, 2018
 *      Author: OS1
 */

#ifndef H_PCBARR_H_
#define H_PCBARR_H_

//forward declaration
class PCB;

class PCBArray{
public:
	//constructor
	PCBArray(int cap = 512);

	//destructor
	~PCBArray();

	//methods
	void addPCB(PCB* pcb);
	PCB* getPCB(int i);
	void removePCB(int i);

	//atributes
	PCB** array;
	int cap;
	int last;

	static PCBArray* allPCBs;
};




#endif /* H_PCBARR_H_ */

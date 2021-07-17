/*
 * PCB.h
 *
 *  Created on: Apr 26, 2020
 *      Author: OS1
 */

#ifndef PCB_H_
#define PCB_H_
#include "Thread.h"



const int nova = 0;
const int spremna = 1;
const int blokirana = 2;
const int zavrsila = 3;

static volatile ID identifikator = 1;

class Queue;
class System;


class PCB {
public:
	PCB(unsigned long velicinaSteka, int kvant1 ,Thread* t);
	virtual ~PCB();
	void kreirajKontekst();
	unsigned sp,ss;
	unsigned bp;

	unsigned* stek;
	unsigned long velicina;
	int stanje;
	Thread*  nit;
	int kvant;

	ID id;
	int semBr;

	Queue* blokirane;




	friend class Queue;
	friend class Thread;

};



#endif /* PCB_H_ */

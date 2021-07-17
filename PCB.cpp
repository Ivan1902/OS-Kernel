/*
 * PCB.cpp
 *
 *  Created on: Apr 26, 2020
 *      Author: OS1
 */

#include "PCB.h"
#include<dos.h>
#include "System.h"
//#include "List.h"
#include "Queue.h"
#include "Thread.h"

//class Thread;


PCB::PCB( unsigned long velicinaSteka, int kvant1,Thread* t) {
#ifndef BCC_BLOCK_IGNORE
lock;

	velicina = velicinaSteka / sizeof(unsigned);
	nit = t;
	blokirane = new Queue();
	stanje = nova;
	kvant = kvant1;
	id = identifikator++;
	semBr = -1;
	stek = new unsigned [velicina];

unlock;
#endif
}

PCB::~PCB() {
#ifndef BCC_BLOCK_IGNORE
lock;
	delete stek;
	delete blokirane;
	//delete nit;
unlock;
#endif
}


void PCB::kreirajKontekst(){
#ifndef BCC_BLOCK_IGNORE
lock;

	stek[velicina - 1] = 0x200;
	stek[velicina - 2] = FP_SEG(&(System::wrapper));
	stek[velicina - 3] = FP_OFF(&(System::wrapper));

	sp = FP_OFF (stek + velicina - 12);
	ss = FP_SEG (stek + velicina - 12);
unlock;
#endif
}




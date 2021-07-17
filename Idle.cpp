/*
 * Idle.cpp
 *
 *  Created on: Apr 30, 2020
 *      Author: OS1
 */

#include "Idle.h"
#include "System.h"
//#include "Thread.h"


extern int syncPrintf(const char *format, ...);

Idle::Idle(/*StackSize stackSize, Time timeSlice */) {
	// TODO Auto-generated constructor stub
	//Thread::Thread(stackSize, timeSlice);

}

Idle::~Idle() {
	// TODO Auto-generated destructor stub
	//Thread::~Thread();
}

void Idle::run(){
	while(1);
}

void Idle::start(){
#ifndef BCC_BLOCK_IGNORE
lock;
	getPCB()->stanje = spremna;
	getPCB()->kreirajKontekst();
	//syncPrintf("usao u start metodu idle niti\n");
unlock;
#endif
}



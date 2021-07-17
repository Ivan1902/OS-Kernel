/*
 * Thread.cpp
 *
 *  Created on: Apr 26, 2020
 *      Author: OS1
 */
#include "Thread.h"
#include "System.h"
#include "SCHEDULE.H"
#include "PCB.h"
//#include "List.h"
#include "Queue.h"




void dispatch(){
#ifndef BCC_BLOCK_IGNORE

	System::dispatch();

#endif
}




Thread::Thread(StackSize stackSize , Time timeSlice ){
#ifndef BCC_BLOCK_IGNORE
lock;
	myPCB = new PCB(stackSize,timeSlice,this);
	System::niti->dodaj(myPCB);

unlock;
#endif
}

Thread::~Thread(){
#ifndef BCC_BLOCK_IGNORE
lock;
	waitToComplete();

	delete myPCB;
	System::niti->ukloni(this);
unlock;
#endif
}


void Thread::start(){
#ifndef BCC_BLOCK_IGNORE
lock;

		if(myPCB->stanje == spremna) {unlock; return;}
		myPCB->stanje = spremna;
		myPCB->kreirajKontekst();
		Scheduler::put((PCB*)myPCB);

unlock;
#endif
}

void Thread::waitToComplete(){
#ifndef BCC_BLOCK_IGNORE
lock;
	if(this->myPCB == System::running){
		unlock;
		return;
	}
	if(this == System:: starting){
		unlock;
		return;
	}
	if(this == System::idle){
		unlock;
		return;
	}
	if(myPCB->stanje == zavrsila){
		unlock;
		return;
	}
	System::running->stanje = blokirana;
	myPCB->blokirane->dodaj((PCB*)System::running);
unlock;
	dispatch();


#endif
}

ID Thread::getId(){
	return myPCB->id;

}

ID Thread :: getRunningId(){
	return System::running->id;
}

Thread* Thread::getThreadById(ID id){
	return System::niti->pretraga(id)->nit;
}

PCB* Thread::getPCB(){
	return myPCB;
}




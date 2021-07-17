/*
 * KerneSem.cpp
 *
 *  Created on: May 6, 2020
 *      Author: OS1
 */

#include "KerneSem.h"
#include "System.h"
#include "SCHEDULE.h"



KernelSem::KernelSem (int init){
#ifndef BCC_BLOCK_IGNORE
lock;
	value = init;
	blokirane = new Queue();

	System::semafori->dodaj(this);

unlock;
#endif
}

KernelSem::~KernelSem (){
#ifndef BCC_BLOCK_IGNORE
lock;
	while(blokirane->getBr()!=0) Scheduler::put(blokirane->ukloni());
	delete blokirane;
unlock;
#endif
}

int KernelSem::wait(Time maxTimeToWait){
#ifndef BCC_BLOCK_IGNORE
lock;

	value--;
	if(value>=0 ){
		System::running->semBr = -1;
		unlock;
		return 1;
	}
	else{

		System::running->stanje = blokirana;

		if(maxTimeToWait > 0) {
			System::running->semBr = maxTimeToWait;
		}
		blokirane->dodaj((PCB*)System::running);

		unlock;
		System::dispatch();
		lock;
		if(System::running->semBr == 0){
			System::running->semBr = -1;
			unlock;
			return 0;
		}
		else {
			System::running->semBr = -1;
			unlock;
			return 1;
		}
	}
#endif
}

int KernelSem::signal(int n){
#ifndef BCC_BLOCK_IGNORE
lock;
	if(n == 0){
		PCB* pom = blokirane->ukloni();
		pom->stanje = spremna;
		Scheduler::put(pom);
		value++;
		unlock;
		return 0;
	}
	if(n > 0){
		value = value + n;
		if(n > blokirane->getBr()) n = blokirane->getBr();
		while(n){
			PCB* pom = blokirane->ukloni();
			pom->stanje = spremna;

			Scheduler::put(pom);
			n--;
		}

		unlock;
		return n;
	}
	if(n < 0){
		unlock;
		return n;
	}
#endif
}

int KernelSem::val() const {
	return value;
}


void KernelSem::umanji(){
#ifndef BCC_BLOCK_IGNORE
lock;
	//syncPrintf("POZIV METODE UMANJI\n");
	blokirane->umanji();
unlock;
#endif
}

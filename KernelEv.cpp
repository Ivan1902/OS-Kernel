/*
 * KernelEv.cpp
 *
 *  Created on: May 15, 2020
 *      Author: OS1
 */

#include "KernelEv.h"
#include "System.h"
#include "PCB.h"
#include "SCHEDULE.H"

KernelEv::KernelEv(IVTNo ivtNo) {
#ifndef BCC_BLOCK_IGNORE
lock;
	this->ivtNo = ivtNo;
	this->value = 0;
	this->vlasnik = System::running->nit;
	System::ivtEntry[ivtNo]->event = this;
unlock;
#endif
}

KernelEv::~KernelEv() {
#ifndef BCC_BLOCK_IGNORE
lock;
	System::ivtEntry[ivtNo]->event = 0;
unlock;
#endif
}

void KernelEv:: signal(){
#ifndef BCC_BLOCK_IGNORE
lock;
	if (this->value == 0 && this->vlasnik->getPCB()->stanje == blokirana){
		this->vlasnik->getPCB()->stanje = spremna;
		Scheduler::put(this->vlasnik->getPCB());
		unlock;
		System::dispatch();
	}
	else {
		value = 1;
		unlock;
	}

#endif
}

void KernelEv:: wait(){
#ifndef BCC_BLOCK_IGNORE
lock;
	if(this->vlasnik == System::running->nit){
		if(value == 0){
			this->vlasnik->getPCB()->stanje = blokirana;
			unlock;
			System::dispatch();
		}else {
			value = 0;
			unlock;
		}
	}else {
		value = 0;
		unlock;
	}
#endif

}


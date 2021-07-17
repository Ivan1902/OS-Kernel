/*
 * IVTEntry.cpp
 *
 *  Created on: May 15, 2020
 *      Author: OS1
 */

#include "IVTEntry.h"
#include "System.h"
#include <dos.h>

IVTEntry::IVTEntry(IVTNo ivtNo, pInterrupt novaRutina) {
#ifndef BCC_BLOCK_IGNORE
lock;
	this->ivtNo = ivtNo;
	this->event = 0;
	System::ivtEntry[ivtNo] = this;

	this->staraRutina = getvect(ivtNo);
	setvect(ivtNo,novaRutina);

unlock;
#endif

}

IVTEntry::~IVTEntry() {
#ifndef BCC_BLOCK_IGNORE
lock;
	setvect(ivtNo, staraRutina);
	System::ivtEntry[ivtNo] = 0;
unlock;
#endif

}


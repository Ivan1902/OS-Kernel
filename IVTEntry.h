/*
 * IVTEntry.h
 *
 *  Created on: May 15, 2020
 *      Author: OS1
 */

#ifndef IVTENTRY_H_
#define IVTENTRY_H_
#include "Event.h"

typedef void interrupt (*pInterrupt)(...);

class IVTEntry {
public:
	IVTEntry(IVTNo ivtNo, pInterrupt novaRutina);
	virtual ~IVTEntry();

	pInterrupt staraRutina;
	KernelEv* event;
	IVTNo ivtNo;


};

#endif /* IVTENTRY_H_ */

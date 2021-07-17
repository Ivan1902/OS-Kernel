/*
 * KernelEv.h
 *
 *  Created on: May 15, 2020
 *      Author: OS1
 */

#ifndef KERNELEV_H_
#define KERNELEV_H_
#include "Thread.h"

typedef unsigned char IVTNo;

class KernelEv {
public:
	KernelEv(IVTNo ivtNo);
	virtual ~KernelEv();
	void wait();
	void signal();

	IVTNo ivtNo;
	int value;
	Thread* vlasnik;
};

#endif /* KERNELEV_H_ */

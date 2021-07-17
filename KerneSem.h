/*
 * KerneSem.h
 *
 *  Created on: May 6, 2020
 *      Author: OS1
 */

#ifndef KERNESEM_H_
#define KERNESEM_H_
#include "Queue.h"

class Queue;

class KernelSem {
public:
	KernelSem(int init);
	virtual ~KernelSem();
	virtual int wait (Time maxTimeToWait);
	virtual int signal(int n=0);
	int val () const;
	int value;
	void umanji();
	Queue* blokirane;

	friend class Queue;
};

#endif /* KERNESEM_H_ */

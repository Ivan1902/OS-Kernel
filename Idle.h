/*
 * Idle.h
 *
 *  Created on: Apr 30, 2020
 *      Author: OS1
 */

#ifndef IDLE_H_
#define IDLE_H_

#include "Thread.h"

class Idle : public Thread {
public:
	Idle(/*StackSize stackSize = defaultStackSize, Time timeSlice =
			defaultTimeSlice*/);
	virtual ~Idle();
	void run();
	void start();

	friend class Thread;
	friend class PCB;
};

#endif /* IDLE_H_ */

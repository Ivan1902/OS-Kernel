/*
 * Semaphor.cpp
 *
 *  Created on: May 6, 2020
 *      Author: OS1
 */

#include "Semaphor.h"
#include "Thread.h"
#include "KerneSem.h"
#include "System.h"


Semaphore::Semaphore (int init){
#ifndef BCC_BLOCK_IGNORE
lock;
	myImpl = new KernelSem(init);
unlock;
#endif
}

Semaphore::~Semaphore (){
#ifndef BCC_BLOCK_IGNORE
lock;
	delete myImpl;
unlock;
#endif
}

int Semaphore::wait(Time maxTimeToWait){
#ifndef BCC_BLOCK_IGNORE
lock;
	int x = myImpl->wait(maxTimeToWait);
unlock;
return x;
#endif
}

int Semaphore::signal(int n){
#ifndef BCC_BLOCK_IGNORE
lock;
	int x =myImpl->signal(n);
unlock;
return x;
#endif
}

int Semaphore::val() const {
	return myImpl->val();
}


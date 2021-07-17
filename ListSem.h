/*
 * ListSem.h
 *
 *  Created on: May 6, 2020
 *      Author: OS1
 */

#ifndef LISTSEM_H_
#define LISTSEM_H_
#include "KerneSem.h"

class ListSem {
public:
	struct Element {
		KernelSem* data;
		Element* sled;
		Element(KernelSem* d1,Element* sled1 = 0){
			data = d1;
			sled = sled1;
		}
	};
	Element* prvi;
	void dodaj(KernelSem* k);
	KernelSem* ukloni();
	int br;
	int getBr();
	void umanji();

	ListSem();
	virtual ~ListSem();
};

#endif /* LISTSEM_H_ */

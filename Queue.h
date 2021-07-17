/*
 * Queue.h
 *
 *  Created on: Apr 29, 2020
 *      Author: OS1
 */

#ifndef QUEUE_H_
#define QUEUE_H_
#include "PCB.h"

class Queue {
public:
	struct Elem {
			PCB* data;
			Elem* sled;
			Elem(PCB* d1,Elem* sled1 = 0){
				data = d1;
				sled = sled1;
			}
		};
		Elem* prvi;

		void dodaj (PCB* t1);
		PCB* ukloni();
		void ukloni(Thread* t);
		PCB* ukloni(PCB* p);
		int br;

		void vracanje();
		PCB* pretraga(ID id);
		int getBr();
		void umanji();

		friend class PCB;

	Queue();
	virtual ~Queue();
};

#endif /* QUEUE_H_ */

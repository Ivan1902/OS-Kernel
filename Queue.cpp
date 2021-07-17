/*
 * Queue.cpp
 *
 *  Created on: Apr 29, 2020
 *      Author: OS1
 */
#include "Queue.h"
#include "System.h"
#include "SCHEDULE.H"



Queue::Queue() {
#ifndef BCC_BLOCK_IGNORE
lock;
	prvi = 0;
	br = 0;
unlock;
#endif
}

Queue::~Queue() {
#ifndef BCC_BLOCK_IGNORE
lock;
	// TODO Auto-generated destructor stub

	Elem* preth = 0;
	while(prvi){
		preth = prvi;
		prvi = prvi->sled;
		delete preth;
		br--;
	}

unlock;
#endif
}


void Queue::dodaj (PCB* d){
#ifndef BCC_BLOCK_IGNORE
lock;
//syncPrintf("DODAVANJE BLOKIRANIH NITI\n");
	if(prvi == 0){
		prvi = new Elem(d);
	}
	else{
		Elem* tek = prvi;
		while(tek->sled) tek = tek->sled;
		tek->sled = new Elem(d);
	}
	br++;
unlock;
#endif
}

PCB* Queue::ukloni(){
#ifndef BCC_BLOCK_IGNORE

	if(prvi == 0) return 0;
lock;
	PCB* pom = prvi->data;
	Elem* tek = prvi;
	if(prvi->sled)prvi = prvi->sled;
	else prvi = 0;
	br--;
	delete tek;
	unlock;
	return pom;

#endif
}

void Queue::vracanje(){
#ifndef BCC_BLOCK_IGNORE
lock;
	while(br) {
		PCB* pom = this->ukloni();
		pom->stanje = spremna;

		Scheduler::put(pom);
	}
unlock;
#endif
}

PCB* Queue::pretraga(ID id){
#ifndef BCC_BLOCK_IGNORE
lock;
	Elem* tek = prvi;
	while(tek){
		if(tek->data->id == id){
			unlock;
			return tek->data;
		}
		tek = tek->sled;
	}
	unlock;
	return 0;

#endif
}

int Queue::getBr(){
	return br;
}

void Queue::ukloni(Thread* t){
#ifndef BCC_BLOCK_IGNORE
lock;
	Elem* tek = prvi;
	Elem* pret = 0;
	while(tek){
		if(tek->data->nit == t){
			br--;
			// OVAJ DEO POPRAVITI NA MODIFIKACIJI
			if(tek == prvi){
				if(prvi->sled) prvi = prvi->sled;
				else prvi = 0;
			}
			else pret->sled = tek->sled;
			delete tek;
			unlock;
			return;
		}
		pret = tek;
		tek = tek->sled;
	}
unlock;
#endif
}

PCB* Queue::ukloni(PCB* p){
#ifndef BCC_BLOCK_IGNORE
lock;

	Elem* tek = prvi;
	Elem* pret = 0;
	while(tek){
		if(tek->data == p){
			br--;
			if(tek == prvi){
				if(prvi->sled) prvi = prvi->sled;
				else prvi = 0;
			}
			else {
				pret->sled = tek->sled;
			}
			//Elem* pom = tek;
			delete tek;
			//syncPrintf("NIT KOJA JE UKLONJENA: %d\n",pom->data->id);
			unlock;
			return p;
		}
		pret = tek;
		tek = tek->sled;
	}
unlock;
return 0;
#endif
}

void Queue::umanji(){
#ifndef BCC_BLOCK_IGNORE
lock;

	Elem* tek = prvi;
	while(tek){

		tek->data->semBr--;
		int i,j;

		if(tek->data->semBr == 0){

			Elem* tmp = tek;
			tek = tek->sled;
			PCB* pom = ukloni(tmp->data);

			pom->stanje = spremna;
			Scheduler::put(pom);



		}

		else{


			if(!tek->sled) break;
			tek = tek->sled;

		}
	}

unlock;
#endif
}





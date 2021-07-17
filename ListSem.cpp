/*
 * ListSem.cpp
 *
 *  Created on: May 6, 2020
 *      Author: OS1
 */

#include "ListSem.h"
#include "System.h"



ListSem::ListSem() {
#ifndef BCC_BLOCK_IGNORE
lock;

	prvi = 0;
	br = 0;

unlock;
#endif
}

ListSem::~ListSem() {
#ifndef BCC_BLOCK_IGNORE
lock;
	// TODO Auto-generated destructor stub
	Element* preth = 0;
	while(prvi){
		preth = prvi;
		prvi = prvi->sled;
		delete preth;
		br--;
	}

unlock;
#endif
}


void ListSem::dodaj (KernelSem* d){
#ifndef BCC_BLOCK_IGNORE
lock;

	if(prvi == 0){
		prvi = new Element(d);

	}
	else{
		Element* tek = prvi;
		while(tek->sled) tek = tek->sled;
		tek->sled = new Element(d);
	}
	br++;
unlock;
#endif
}

KernelSem* ListSem::ukloni(){
#ifndef BCC_BLOCK_IGNORE

	if(prvi == 0) return 0;
lock;
	KernelSem* pom = prvi->data;
	Element* tmp = prvi;
	prvi = prvi->sled;
	br--;
	delete tmp;
	unlock;
	return pom;

#endif
}

int ListSem::getBr(){
	return br;
}

void ListSem::umanji(){
#ifndef BCC_BLOCK_IGNORE
lock;

	Element* tek = prvi;
	while(tek){

		tek->data->umanji();
		tek = tek->sled;
	}
unlock;
#endif
}


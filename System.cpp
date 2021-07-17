/*
 * System.cpp
 *
 *  Created on: Apr 26, 2020
 *      Author: OS1
 */

#include "System.h"
//#include "PCB.h"
#include "SCHEDULE.H"

#include "Thread.h"
#include "Queue.h"
#include "ListSem.h"



System::System() {
	// TODO Auto-generated constructor stub

}

System::~System() {
	// TODO Auto-generated destructor stub
}



volatile PCB* System::running = 0;
Idle* System::idle = 0;
Thread* System::starting = 0;
Queue* System::niti = 0;
volatile int System::context_switch_on_demand = 0;
pInterrupt System::staraRutina = 0;
volatile int System::cntr = 0;
ListSem* System::semafori = new ListSem();
IVTEntry* System::ivtEntry[256] = {0};




void System::init_system(){
#ifndef BCC_BLOCK_IGNORE
lock;

	staraRutina = getvect(0x08);
	setvect(0x08,timer);
	setvect(0x60,staraRutina);

	niti = new Queue();



	starting = new Thread();
	starting->getPCB()->stanje = spremna;

	running = (volatile PCB*) starting->getPCB();


	idle = new Idle();
	idle->start();


unlock;
#endif
}

void System::restore_system(){
#ifndef BCC_BLOCK_IGNORE
if( (PCB*)running != starting->getPCB()) return;
lock;

	setvect(0x08,staraRutina);

	delete idle;
	delete starting;
	delete niti;

unlock;
#endif
}

void System::dispatch(){
#ifndef BCC_BLOCK_IGNORE
lock;
	context_switch_on_demand = 1;
unlock;
	timer();

#endif
}

void interrupt System::timer(...){
#ifndef BCC_BLOCK_IGNORE

	if(!context_switch_on_demand){
			semafori->umanji();
		}
	//syncPrintf("usao u metodu timer, aktivna nit: %d\n",running->id);
	if(!context_switch_on_demand) {

			asm int 60h;
			tick();

		}


	if((running->kvant == 0) && !(context_switch_on_demand))  return;
	if (!context_switch_on_demand) cntr++;

	if (cntr == running->kvant || context_switch_on_demand) {

		asm {
			// cuva sp
			mov tsp, sp
			mov tss, ss
		}

		running->sp = tsp;
		running->ss = tss;




		// scheduler

		if(running->stanje == spremna && running!=idle->getPCB()) {

			Scheduler::put((PCB*)running);
		}

		running = (volatile PCB*) Scheduler::get();


		if(running == 0 ) {
			running = idle->getPCB();

		}

		tsp = running->sp;
		tss = running->ss;

		cntr = 0;


		asm {
			// restaurira sp
			mov sp, tsp
			mov ss, tss
		}
	}




	context_switch_on_demand = 0;


#endif
} // kraj rutine tajmer

void System::wrapper(){
#ifndef BCC_BLOCK_IGNORE
	running->nit->run();
lock;

	running->stanje = zavrsila;


	running->blokirane->vracanje();

unlock;

dispatch();
#endif
}





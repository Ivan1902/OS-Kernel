/*
 * System.h
 *
 *  Created on: Apr 26, 2020
 *      Author: OS1
 */

#ifndef SYSTEM_H_
#define SYSTEM_H_
#include<dos.h>
#include "PCB.h"
//#include "List.h"
#include "Idle.h"
#include "Queue.h"
#include "ListSem.h"
#include "IVTEntry.h"


#define lock asm{\
 	pushf;\
 	cli;\
}

// dozvoljava prekide
#define unlock asm popf

// potpis interrupt rutine za rad sa setvect()
// i getvect()
typedef void interrupt (*pInterrupt)(...);

// stara prekidna rutina
static pInterrupt staraRutina;

extern void tick();

static int cntr;

static unsigned tsp;
static unsigned tss;



class Thread;




class System {
public:


	System();
	virtual ~System();

	static volatile PCB* running;
	static Idle* idle;
	static Thread* starting;
	static Queue* niti;
	static volatile int context_switch_on_demand;
	static pInterrupt staraRutina;
	static volatile int cntr;
	static ListSem* semafori;
	static IVTEntry* ivtEntry[256];

	static void init_system();
	static void restore_system();
	static void interrupt timer(...);
	static void wrapper();
	static void dispatch();


	friend class Thread;
	friend class PCB;
	friend class Queue;
};



#endif /* SYSTEM_H_ */

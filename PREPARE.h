/*
 * PREPARE.h
 *
 *  Created on: May 15, 2020
 *      Author: OS1
 */

#ifndef PREPARE_H_
#define PREPARE_H_
#include "System.h"
#include "IVTEntry.h"
#include "KernelEv.h"

#define PREPAREENTRY(ivtNo,oldRoutine) \
void interrupt interruptHandler##ivtNo(...); \
IVTEntry ulaz##ivtNo(ivtNo, interruptHandler##ivtNo); \
void interrupt interruptHandler##ivtNo(...){ \
    if (oldRoutine == 1) ulaz##ivtNo.staraRutina(); \
		ulaz##ivtNo.event -> signal(); \
		}



#endif /* PREPARE_H_ */

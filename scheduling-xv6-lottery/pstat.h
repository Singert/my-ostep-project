#ifndef _PSTAT_H
#define _PSTAT_H

#include "param.h"

enum procstate { UNUSED, EMBRYO, SLEEPING, RUNNABLE, RUNNING, ZOMBIE };

struct pstat {
	_Bool inuse[NPROC];

	// PID of each process
	int pid[NPROC];

	// Number of ticks each process has accumulated
	int ticks[NPROC];

	// Number of tickets
	int tickets[NPROC];
    
	//state
	enum procstate state[NPROC];
	int total_tickets;
};

#endif
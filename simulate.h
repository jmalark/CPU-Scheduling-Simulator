#ifndef SIMULATE_H
#define SIMULATE_H

#include<iostream>
#include <chrono>
#include "Scheduler.h"
#include "Process.h"


double* simulate(Scheduler* sched, int numCPUBound, int numIOBound, int numCycles);


#endif

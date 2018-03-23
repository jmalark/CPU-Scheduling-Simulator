#include "simulate.h"
#include "Scheduler.h"
#include "Process.h"
#include <iostream>
#include <chrono>
#include <queue>

using namespace std;

double* simulate(Scheduler* sched, int numCPUBound, int numIOBound, int numCycles)
{//make a queue
  queue<Process*> queue;

//allocate and add Processes
  //CPUBound's ID = 1, IOBound's ID = 2
  for(int CPUB = 0; CPUB < numCPUBound; ++CPUB)
    {
      Process* proc = new CPUBoundProcess(1);
      sched->addProcess(proc);
      queue.push(proc);
    }
  
  for(int IOB = 0; IOB < numIOBound; ++IOB)
    {Process* proc = new IOBoundProcess(2);
      sched->addProcess(proc);
      queue.push(proc);
    }
  
  
  
  //main loop, runs the correct number of cycles
  int cycleHolder = 0;
  double schedUsedCount = 0;
  auto t1 = chrono::system_clock::now();
  while (cycleHolder < numCycles)
    {
      auto nextPro = sched->popNext(cycleHolder);
      int tempNumCycles = nextPro->simulate(cycleHolder, 10);
      cycleHolder += tempNumCycles;
      sched->addProcess(nextPro);
      ++schedUsedCount; 
      
    }
  auto t2 = chrono::system_clock::now();
  auto dur = t2 - t1;
  auto durNano = chrono::duration_cast<chrono::nanoseconds>(dur);
  double elipsed = durNano.count();

  
  double totalCPUCPUB = 0;
  double totalCPUIOB = 0;
  double totalWaitCPUB = 0;
  double totalWaitIOB = 0;

  //get info from and then delete the allocated processes
  for(int inQueue = 0; inQueue < (numCPUBound + numIOBound); ++inQueue)
    {auto proc = queue.front();
      queue.pop();
      
      //if it's CPUBound
      if (proc->getID() == 1)
	{totalCPUCPUB += proc->getCPUTime();
	  totalWaitCPUB += proc->getWaitTime(cycleHolder);
	}
      //if it's IOBound
      else if (proc->getID() == 2)
	{totalCPUIOB += proc->getCPUTime();
	  totalWaitIOB += proc->getWaitTime(cycleHolder);
	}
      delete proc;
    }


  double* endArr = new double[5];

  //currently if any of the quantities of CPU or IO Bound processes are 0, -nan will be printed from the array in schedulersim, becasue anything/0 is undefined 

  //time passed/times it used the scheduler
  endArr[0]= elipsed/schedUsedCount;
  //avg CPU time of CPUBound
  endArr[1] = totalCPUCPUB / numCPUBound;

  //avg wait time CPUBound
  endArr[2] = totalWaitCPUB / numCPUBound;

  //avg CPU time of IOBound
  endArr[3] = totalCPUIOB / numIOBound;
  //avg wait time of IOBound
  endArr[4] = totalWaitIOB / numIOBound;

      
  return endArr;

}

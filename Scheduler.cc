#include "Scheduler.h"
#include <iostream>
#include "Process.h"
#include "ArrayList.h"
#include <typeinfo>
#include "LinkedList.h"
#include "BSTMultimap.h"
#include "RBTMultimap.h"
using namespace std;

//initializes procQueue as an empty ArrayList
RoundRobin::RoundRobin()
{procQueue = new ArrayList<Process*>;
}

//deletes procQueue (not its contents!)
RoundRobin::~RoundRobin()
{delete procQueue;
}

//adds the given process to the back of procQueue.
void RoundRobin::addProcess(Process* proc)
{procQueue->pushBack(proc);
}

//pops the process at the front of the queue and returns it.
Process* RoundRobin::popNext(int curCycle)
{Process* ans = procQueue->getFront();
  procQueue->popFront();
  return ans;  
}

FastRoundRobin::FastRoundRobin()
{delete procQueue;
  procQueue = new LinkedList<Process*>;

}



//initializes procTree as an empty BSTMultimap
CompletelyFair::CompletelyFair()
{procTree = new BSTMultimap<int, Process*>;
}

//deletes procTree (not its contents!)
CompletelyFair::~CompletelyFair()
{delete procTree;
}


//adds the given process to procTree (current CPU time as key)
void CompletelyFair::addProcess(Process* proc)
{procTree->insert(proc->getCPUTime(), proc);
}

  /*First obtain an iterator pointing to the process with the minimum CPU time. Then use the iterator to traverse the tree until you find a process that is not blocked. Remove and return that process.*/
Process* CompletelyFair::popNext(int curCycle)
{BSTForwardIterator<int, Process*> min = procTree->getMin();
  

  while((min.getValue())->isBlocked(curCycle))
    {min.next();
    }
  
      Process* tempProcess = min.getValue();
  procTree->remove(min);

  return tempProcess;
 
}

FastCompletelyFair::FastCompletelyFair()
{delete procTree;
  procTree = new RBTMultimap<int, Process*>;
}

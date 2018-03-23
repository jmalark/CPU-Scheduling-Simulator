#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "List.h"
#include "Process.h"
#include "BSTMultimap.h"

//abstract base class
class Scheduler
{
 public:

  //deconstructor to inherit (empty, just for inheritence)
  virtual ~Scheduler() { }

  //adds the given process to the processes to be scheduled
  virtual void addProcess(Process* proc) = 0;
  
  //removes and returns the next process in the schedule
  virtual Process* popNext(int curCycle) = 0;




};

//concrete
class RoundRobin : public Scheduler
{
 protected:
  List<Process*>* procQueue;

 public:
  //initializes procQueue as an empty ArrayList.
  RoundRobin();

  //deletes procQueue (but not its contents)
  virtual ~RoundRobin();

  //adds the given process to the back of procQueue
  virtual void addProcess(Process* proc);

  //pops the process at the front of the queue and returns it
  virtual Process* popNext(int curCycle);


};

//subclass of RoundRobin, used linked lists instead of array backed
class FastRoundRobin : public RoundRobin
{public:
  //initializes procQueue as an empty LinkedList.
  FastRoundRobin();

};


//concrete
class CompletelyFair : public Scheduler
{
 protected:
  BSTMultimap<int, Process*>* procTree;

 public:
  //initializes procTree as an empty BSTMultimap.
  CompletelyFair();

  //deletes procTree (not its contents!)
  virtual ~CompletelyFair();

  //adds the given process to procTree (current CPU time as key)
  virtual void addProcess(Process* proc);

  /*First obtain an iterator pointing to the process
with the minimum CPU time. Then use the iterator to traverse the tree until you find a process that is not blocked. Remove and return that process.*/
  virtual Process* popNext(int curCycle);


};


class FastCompletelyFair : public CompletelyFair
{public:
  //deletes completelyfair's tree and makes procTree a RBTMultimap
  FastCompletelyFair();


};



#endif

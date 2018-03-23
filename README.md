# CPU-Scheduling-Simulator

Jessica Malark
CPS 222 Project 2

Files submitted:
List.h
ArrayList.h
LinkedList.h
LinkedListNode.h
Process.h
Process.cc
Scheduler.h
Scheduler.cc
simulate.h
simulate.cc
schedulesim.cc
Makefile
timing.pdf
cputimes.pdf
BSTMultimap.h
BSTNode.h
BSTForwardIterator.h
RBTNode.h
RBTMultimap.h
README.md

This project has one main program with several pieces to it. “make all” will compile the project or you can compile it with the alternative command provided below.


---schedulesim---
To compile: make schedulesim 
To run: ./schedulesim <numCPUBound> <numIOBound> <numCycles>

Description:
schedulesim is a program that collects data about the performance of various types of schedulers. The schedulers hold IO Bound and CPU Bound processes and determine which processes get CPU time. It takes command line arguments for how many CPU and IO Bound processes there should be, as well as the number of cycles that it should run. There are four types of schedulers, RoundRobin, FastRoundRobin, CompletelyFair and FastCompletelyFair. For each type of scheduler the program prints out its overhead time and the CPU and Wait times for CPU and IO Bound processes. 



Known issues:
-running simulations with only IO bound processes can result in all of the processes becoming blocked at once (especially with lower amounts of IO bound processes). So don’t do that.

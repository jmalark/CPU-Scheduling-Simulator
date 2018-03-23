#include "simulate.h"
#include <iostream>
#include <cstdlib>
#include <string>
using namespace std;

//command args: num CPU-bound processes, num I/O-bound, num cycles to simulate
int main(int argc, char** argv)
{ Scheduler* schedArr[4];

RoundRobin schedRR; 
RoundRobin* ptSchedRR = &schedRR; 
 FastRoundRobin schedFRR;
 FastRoundRobin* ptSchedFRR = &schedFRR;
 CompletelyFair schedCF;
 CompletelyFair* ptSchedCF = &schedCF;
 FastCompletelyFair schedFCF;
 FastCompletelyFair* ptSchedFCF= &schedFCF;

 schedArr[0] = ptSchedRR;
 schedArr[1]= ptSchedFRR;
 schedArr[2] = ptSchedCF;
 schedArr[3] = ptSchedFCF;

 string descrArr[4];
 descrArr[0] = "\nRoundRobin Results: \nOverhead  Avg CPU Time(CPU)  Avg Wait(CPU)  Avg CPU Time(IO)  Avg Wait(IO)\n";
 descrArr[1] = "FastRoundRobin Results: \nOverhead  Avg CPU Time(CPU)  Avg Wait(CPU)  Avg CPU Time(IO)  Avg Wait(IO)\n";
 descrArr[2] = "CompletelyFair Results: \nOverhead  Avg CPU Time(CPU)  Avg Wait(CPU)  Avg CPU Time(IO)  Avg Wait(IO)\n";
descrArr[3] = "FastCompletelyFair Results: \nOverhead  Avg CPU Time(CPU)  Avg Wait(CPU)  Avg CPU Time(IO)  Avg Wait(IO)\n";


 for(int i = 0; i < 4; ++i)
   {double* ansArr = simulate(schedArr[i], atoi(argv[1]), atoi(argv[2]), atoi(argv[3]));
     
     
     cout << descrArr[i];

     /*
     cout << "approximate overhead for scheduler use: " << ansArr[0]<< endl;
     cout << "average CPU time for CPU bound: " << ansArr[1] << endl;
     cout << "average wait time CPU bound: " << ansArr[2]<< endl;
     cout << "average CPU time IO bound: " << ansArr[3]<< endl;
     cout << "average wait time IO bound: " << ansArr[4]<< endl<<endl;
     */

     for(int idx = 0; idx < 5; ++idx)
       {cout<< ansArr[idx]<< "\t\t";
       }
     cout<<endl<<endl;

 delete[] ansArr;
   }
}

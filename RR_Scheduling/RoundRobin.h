#ifndef ROUNDROBIN_H
#define ROUNDROBIN_H

#include "process.h"
#include "unblock_compare.h"

#include <list>
#include <queue>
#include <vector>
#include <iostream>

class RoundRobin {
public:
 /**
   * Constructor
   * 
   * @param processVector --> vector of processes to schedule
   * @param block_time --> block time duration given by the command line
   * @param time_slice --> time slice (quantum) given by the command line 
   */
    RoundRobin(std::vector<process> &processVector,int block_time, int time_slice); 
 /**
   * run --> run the RoundRobin simulation
   */
    void run();

    
    int process_time_slice(std::list<process>::iterator process);
    
    // Vectors and priority que needed to run RoundRobin
    std::vector<std::list<process>::iterator> next;
    std::priority_queue<process, std::vector<process>, unblock_compare> blocked; 
    std::vector<std::list<process>> ready;
     
private:
   
    // Private variables needed
    int block_duration = 0;
    int total_times = 0;
    int terminations = 0;
    int time_slice = 0;
    int time = 0;

   
};

#endif /* ROUNDROBIN_H */
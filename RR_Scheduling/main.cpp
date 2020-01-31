#include "process.h"
#include "RoundRobin.h"

#include <fstream>
#include <iostream>
#include <list>
#include <queue>
#include <sstream>
#include <vector>



/**
 * Main program
 */
int main(int argc, char *argv[]) {

  
  // Convert command line string argument to an int
  int block_time = atoi(argv[2]);
  int time_slice = atoi(argv[3]);
  
  // Open file
  std::fstream input_file;
  input_file.open(argv[1]);

  std::string line_to_parse; 
  std::vector<process> processes; 
  
  // Parse lines of the file
  while(getline(input_file, line_to_parse)) { 
    
    std::istringstream stream(line_to_parse);
    std::string input_process;
    int input_priority;
    int input_arrival_time;
    int input_total_time;
    int input_block_interval;

    stream >> input_process;
    stream >> input_priority;
    stream >> input_arrival_time;
    stream >> input_total_time; 
    stream >> input_block_interval;
    
    // Create a process for each line
    process a(input_process,input_priority,input_arrival_time,input_total_time,input_block_interval);
    
    // Add it to the process vector
    processes.push_back(a);
   
  }
  
  // Create RoundRobin object and run the function 
  RoundRobin roundRobin(processes,block_time, time_slice);
  roundRobin.run();
}
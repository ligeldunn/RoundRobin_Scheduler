#include "RoundRobin.h"

#include <iostream>




RoundRobin::RoundRobin(std::vector<process> &processVector, int block_duration, int time_slice): ready(10){
    
    // Initialize values
    this->block_duration = block_duration;
    this->time_slice = time_slice;
    time = 0;
    
    // Place all processes in blocked que to start
    for (size_t i = 0; i < processVector.size(); i++){
       process a = processVector[i];
       blocked.emplace(a);
    }
 
    
}

void RoundRobin::run(){
    
    std::cout << block_duration << " " << time_slice << "\n"; 
    
    // Initialization of variables
    int priority = -1;
    int highest_priority_ready = 0;
    total_times = 0;
    terminations = 0;
    int time_to_slice = 0;
    std::list<process>::iterator tempIterator;
    
    
    // Initialization of next que
    for(int i = 0; i < next.size(); i++){
        next.erase(next.begin());
    }
    for(size_t i = 0; i <= 9; i++){
        
         tempIterator = ready.at(i).end();
         next.push_back(tempIterator);
    }
   
    while(true){
        
        // Finding the highest priority that is ready
        bool find_success = false;
        for (int i = 9; i >= 0; i--) {
            if (!ready.at(i).empty()) {
                highest_priority_ready = i;
                find_success = true;
                break;
            }
        }
        if (!find_success) {
            highest_priority_ready = -1;
        }
        
        if(highest_priority_ready < 0 && blocked.empty()){
            break;
        }
        
        // Move unblocked process to ready
        while(!blocked.empty() && blocked.top().get_unblock_time() <= time){
            process temp = blocked.top();
            blocked.pop();
            temp.set_block_time(temp.get_block_interval());
            ready.at(temp.get_priority()).push_back(temp);
        }
        
        // Setting priority to the highest priority that is ready
        find_success = false;
        for(int i = 9; i >= 0; i--){
            if(!ready.at(i).empty()){
                priority = i;
                find_success = true;
                break;
            }
        }
        if(!find_success){
            priority = -1;
        }
        // If priority is in the ready start next one
        if(priority >= 0){
            
            if(next.at(priority) == ready.at(priority).end()){           
                next.at(priority) = ready.at(priority).begin();
       
            }       
            
            // Get the correct process and update que with iterator 
            
            tempIterator = next.at(priority);
            time_to_slice = process_time_slice(tempIterator);
            next.at(priority)++;
            
            
        // If not start idle    
        }else{      
            time_to_slice = blocked.top().get_unblock_time() - time;       
        
            std::cout << " " << time << "\t" << "(IDLE)" << "\t" << time_to_slice << "\t" << "I" << "\n";    
        }
      
        time += time_to_slice;
        
   }
    
    float average_time = (float) total_times / terminations;  
    std::cout << " " << time << "\t" << "(END)" << "\t" << average_time << "\n";
}

int RoundRobin::process_time_slice(std::list<process>::iterator process){
       
        // Setting when to slice the process between time_slice, bock_time, and time_remaining

        int temp = 0;
        if(time_slice < process->get_time_remaining()){
            temp = time_slice;
        }else if(time_slice == process->get_time_remaining()) {
            temp = time_slice;
        }else{
            temp = process->get_time_remaining();
        }
       
        int time_to_slice = 0;
        if(temp < process->get_block_time()){
            time_to_slice = temp;
        }else if(temp == process->get_block_time()) {
            time_to_slice = temp;
        }else{
            time_to_slice = process->get_block_time();
        }
       
        
        int priority = process->get_priority();
        process->time_decrease(time_to_slice);
        
        // Determine the status 
        char charTemp = 'S';
        
        if(process->get_block_time() <= 0){
            charTemp = 'B';
        }
        if(process->get_time_remaining() <= 0){
            charTemp = 'T';
        }
        
        std::cout << " " << time << "\t" << process->get_name() << "\t" << time_to_slice << "\t" << charTemp << "\n";
       
        // Determining what to do if terminated or blocked
        if(charTemp == 'B'){
            
            int new_unblock_time = time + time_to_slice + block_duration;
            process->set_unblock_time(new_unblock_time);
            next.at(priority) = ready.at(priority).erase(process);
            process->set_block_time(process->get_block_interval());
            blocked.push(*process);
            
        }
         if(charTemp == 'T'){
            
            terminations++;
            
            next.at(priority) = ready.at(priority).erase(process);
            total_times += time + time_to_slice - process->get_arrival_time();
        } 
        
        return time_to_slice;
}
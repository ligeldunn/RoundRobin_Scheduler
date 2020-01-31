#include "process.h"

process::process(std::string name, int priority, int arrival_time, int total_time, int block_interval) {
    
    // Initialization
    this->name = name;
    this->priority = priority;
    this->arrival_time = arrival_time;
    this->total_time = total_time;
    this->block_interval = block_interval;
    this->time_remaining = total_time;
    this->unblock_time = arrival_time;
    this->block_time = block_interval;
}

void process::time_decrease(int num){
    time_remaining -= num;
    block_time -= num;
}

// Setter methods 
void process::set_block_time(int t){
    block_time = t;
}
    
void process::set_unblock_time(int t){
    unblock_time = t;
}

// Getter methods
std::string process::get_name(void){
        return name;
}
int process::get_priority(void){
        return priority;
}
int process::get_arrival_time(void){
        return arrival_time;
}
int process::get_total_time(void){
        return total_time;
}
int process::get_block_interval(void){
        return block_interval;
}
int process::get_time_remaining(void){
        return time_remaining;
} 
    
int process::get_unblock_time(void) const{
        return unblock_time;
}
    
int process::get_block_time(void){
        return block_time;
}
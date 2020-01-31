#ifndef PROCESS_H
#define PROCESS_H

#include <string>

class process {
public:
 /**
   * Constructor
   * 
   * @param name --> name of process
   * @param priority --> priority level of process
   * @param arrival_time --> time that the process arrives
   * @param total_time --> total burst time of the process
   * @param block_interval --> block time for the process
   */
    process(std::string name, int priority, int arrival_time, int total_time, int block_interval);
    
   
    // Decrease time function
    void time_decrease(int num);
    
    // Setter methods
    void set_block_time(int t);
    void set_unblock_time(int t);
    
    // Getter methods
    std::string get_name(void);
    int get_priority(void);
    int get_arrival_time(void);
    int get_total_time(void);
    int get_time_remaining(void);
    int get_block_interval(void);
    int get_block_time(void);
    int get_unblock_time(void) const;
    
    
private:
    // Private variables needed
    int block_time;
    int unblock_time;
    int time_remaining; 
    std::string name;
    int priority;
    int arrival_time;
    int total_time;
    int block_interval;
    
};

#endif /* PROCESS_H */

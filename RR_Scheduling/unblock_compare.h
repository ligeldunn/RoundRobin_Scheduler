#ifndef UNBLOCK_COMPARE_H
#define UNBLOCK_COMPARE_H

#include "process.h"

    // Compares the unblock times for priority queue
    class unblock_compare{
    public: 
        bool operator() (process &process_1, process &process_2)  {
            return process_1.get_unblock_time() >= process_2.get_unblock_time();
        }
    };

#endif /* UNBLOCK_COMPARE_H */


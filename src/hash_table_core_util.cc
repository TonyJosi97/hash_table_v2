#include <math.h>
#include <chrono>

#include "../inc/hash_table_util.hpp"

#define UNUSED(X)                       (void)X      /* To avoid gcc/g++ warnings */

static unsigned int     check_if_prime(unsigned int);


unsigned long 
__ht_core_util_get_hash(
    const unsigned long key, 
    const unsigned long capacity, 
    unsigned int chain_degreee) {

    UNUSED(chain_degreee);
    return (key % capacity);

}

unsigned int 
check_if_prime(
    unsigned int num) {

    if(num < 2)
        return 1;
    if(num < 4)
        return 0;
    if((num % 2) == 0)
        return 1;

    for(unsigned int itr = 3; itr <= floor(sqrt((double) num)); itr += 2)
        if((num % itr) == 0)
            return 1;
    return 0;
}



unsigned int     
get_next_prime(unsigned int base) {

    while(check_if_prime(base) != 0)
        ++base;

    return base;
}


unsigned long 
get_time_in_nanosec(
    void) {
    auto now = std::chrono::system_clock::now();
    auto duration = now.time_since_epoch();
    auto nanoseconds =  std::chrono::duration_cast<std::chrono::nanoseconds>(duration);
    auto val = nanoseconds.count();
    unsigned long lval = val;
    return lval;
}


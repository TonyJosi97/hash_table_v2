#include <math.h>
#include <chrono>

#include "../inc/hash_table_util.hpp"

#define UNUSED(X)                       (void)X      /* To avoid gcc/g++ warnings */

static unsigned int     check_if_prime(size_t);


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
    size_t num) {

    if(num < 2)
        return 1;
    if(num < 4)
        return 0;
    if((num % 2) == 0)
        return 1;

    for(unsigned int itr = 3; itr <= floor(sqrt(num)); itr += 2)
        if((num % itr) == 0)
            return 1;
    return 0;
}



size_t
get_next_prime(size_t base) {

    while(check_if_prime(base) != 0)
        ++base;

    return base;
}


unsigned long 
get_time_in_nanosec(
    void) {
    struct timespec ts;
    timespec_get(&ts, TIME_UTC);
    return static_cast<unsigned long>(ts.tv_sec * 1000000000L + ts.tv_nsec);
}



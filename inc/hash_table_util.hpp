/** 
 *  @file   hash_table_util.hpp
 *  @brief  Library function defintions
 *
 *  This contains helper function defintions
 *
 *  @author         Tony Josi   https://tonyjosi97.github.io/profile/
 *  @copyright      Copyright (C) 2020 Tony Josi
 *  @bug            No known bugs.
 */

#include "hash_table_v2.hpp"

unsigned long    __ht_core_util_get_hash(const unsigned long, const unsigned long, unsigned int);
unsigned long    get_time_in_nanosec(void);
unsigned int     get_next_prime(unsigned int);


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

#ifndef _HASH_TABLE_UTIL_H
#define _HASH_TABLE_UTIL_H

#include "hash_table_v2.hpp"

size_t           __ht_core_util_get_hash(const unsigned long, const unsigned long, unsigned int);
unsigned long    get_time_in_nanosec(void);
size_t           get_next_prime(size_t);

#endif /* _HASH_TABLE_UTIL_H */

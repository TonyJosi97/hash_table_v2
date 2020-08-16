/** 
 *  @file   hash_table_v2.hpp
 *  @brief  Master Header file for Hash Table Library
 *
 *  This contains the Header file for data structure & basic funcs.
 *  defs used for the Hash Table library
 *
 *  @author         Tony Josi   https://tonyjosi97.github.io/profile/
 *  @copyright      Copyright (C) 2020 Tony Josi
 *  @bug            No known bugs.
 */

#ifndef _HASH_TABLE_V2_H
#define _HASH_TABLE_V2_H

#include <stddef.h>

namespace ht_v2 {

    struct _ght_item {

        unsigned long       key;        /*!< Key of the item */
        bool                is_active;
        void               *val_ptr;    /*!< Pointer to the item record */

    };

    class hash_table {

        private:
            size_t              base_capacity;      /*!< Base capacity of Hash Table */
            size_t              capacity;           /*!< Current capacity of Hash Table */
            size_t              item_size;          /*!< Size of an item in Hash Table */
            size_t              count;              /*!< Current count items in Hash Table */
            unsigned int        scaling_factor;     /*!< Current number of up scalings, 
                                                        decreased on scale down */
            struct _ght_item   *items;              /*!< Pointer to the items memory of Hash Table */
    };

    
}

#endif /* _HASH_TABLE_V2_H */


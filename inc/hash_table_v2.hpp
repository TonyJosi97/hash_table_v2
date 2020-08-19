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

    typedef enum {
        HT_SUCCESS = 0,        /*!< HT Function success */
        HT_KEY_ALRDY_EXISTS,   /*!< HT Key Already exists */
        HT_EMPTY,              /*!< HT Hash table empty */
        HT_ITEM_NOT_FOUND,     /*!< HT Item is not present in hash table */
        HT_INVALID_PARAMS,     /*!< HT Invalid function params */
        HT_FAIL                /*!< HT Function Fail */
    } ht_ret_status_t;

    class hash_table {

        private:
            size_t              base_capacity;      /*!< Base capacity of Hash Table */
            size_t              capacity;           /*!< Current capacity of Hash Table */
            size_t              item_size;          /*!< Size of an item in Hash Table */
            size_t              count;              /*!< Current count items in Hash Table */
            int                 scaling_factor;     /*!< Current number of up scalings, 
                                                        decreased on scale down */
            struct _ght_item   *items;              /*!< Pointer to the items memory of Hash Table */

            void swap_hash_t_objs(hash_table &obj1, hash_table &obj2); /* Swaps 2 `hash_table` objects */
            int __ht_core_util_scale_up();
            int __ht_core_util_scale_down();
            int __ht_core_util_resize();
            int __ht_core_util_item_init(struct _ght_item *items, unsigned long key, void *val);

        public:
            explicit hash_table(size_t base_capacity, size_t capacity, size_t item_size, size_t count, int scaling_factor);
            hash_table(const hash_table &copy_ob);
            hash_table & operator=(const hash_table &copy_ob);
            hash_table(hash_table &&move_ob);
            hash_table & operator=(hash_table &&move_ob);
            ~hash_table();

            ht_ret_status_t ht_insert(unsigned long key, void *val_ptr);
            ht_ret_status_t ht_find(unsigned long, size_t &);
            ht_ret_status_t ht_get(unsigned long, void *);
            ht_ret_status_t ht_delete(unsigned long);
            unsigned long ht_generate_key();
    };
  
}

#endif /* _HASH_TABLE_V2_H */


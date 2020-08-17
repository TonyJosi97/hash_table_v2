/** 
 *  @file   hash_table_core.c
 *  @brief  Library function defintions
 *
 *  This contains the Library function defintions
 *
 *  @author         Tony Josi   https://tonyjosi97.github.io/profile/
 *  @copyright      Copyright (C) 2020 Tony Josi
 *  @bug            No known bugs.
 */

#include <algorithm>

#include "../inc/hash_table_v2.hpp"

ht_v2::hash_table::hash_table(
    size_t      base_capacity, 
    size_t      capacity, 
    size_t      item_size, 
    size_t      count, 
    int         scaling_factor) 

    : base_capacity     { base_capacity }
    , capacity          { capacity }
    , item_size         { item_size }
    , count             { count }
    , scaling_factor    { scaling_factor }
    , items             { new struct _ght_item[capacity] } {

    void *_t_mem = operator new(capacity * item_size);
    for(int i = 0; i < capacity; ++i) {
        items[i].is_active = false;
        items[i].val_ptr = _t_mem + item_size * i;
    }

}

ht_v2::hash_table::hash_table(
    const hash_table &copy_ob)

    : base_capacity     { copy_ob.base_capacity }
    , capacity          { copy_ob.capacity }
    , item_size         { copy_ob.item_size }
    , count             { copy_ob.count }
    , scaling_factor    { copy_ob.scaling_factor }
    , items             { copy_ob.items } {

    for(int i = 0; i < capacity; ++i) {
        items[i].is_active = copy_ob.items[i].is_active;
        items[i].val_ptr = copy_ob.items[i].val_ptr;
    }

}

void ht_v2::hash_table::swap_hash_t_objs(ht_v2::hash_table &obj1, ht_v2::hash_table &obj2) {
    
    std::swap(obj1.base_capacity,   obj2.base_capacity);
    std::swap(obj1.capacity,        obj2.capacity);
    std::swap(obj1.item_size,       obj2.item_size);
    std::swap(obj1.count,           obj2.count);
    std::swap(obj1.scaling_factor,  obj2.scaling_factor);
    std::swap(obj1.items,           obj2.items);

    for(int i = 0; i < capacity; ++i) {
        std::swap(obj1.items[i].is_active,      obj2.items[i].is_active);
        std::swap(obj1.items[i].val_ptr,        obj2.items[i].val_ptr);
    }
}

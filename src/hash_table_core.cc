/** 
 *  @file   hash_table_core.cc
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
    , items             { capacity ? new struct _ght_item[capacity] : 0 } {

    void *_t_mem = operator new(capacity * item_size);
    for(int i = 0; i < capacity; ++i) {
        items[i].is_active = false;
        items[i].val_ptr = static_cast<char*>(_t_mem) + item_size * i;
    }

}

ht_v2::hash_table::hash_table(
    const ht_v2::hash_table &copy_ob)

    : base_capacity     { copy_ob.base_capacity }
    , capacity          { copy_ob.capacity }
    , item_size         { copy_ob.item_size }
    , count             { copy_ob.count }
    , scaling_factor    { copy_ob.scaling_factor }
    , items             { capacity ? new struct _ght_item[capacity] : 0 } {

    void *_t_mem = operator new(capacity * item_size);
    for(int i = 0; i < capacity; ++i) {
        items[i].is_active = copy_ob.items[i].is_active;
        items[i].val_ptr = static_cast<char*>(_t_mem) + item_size * i;
        memcpy(items[i].val_ptr, copy_ob.items[i].val_ptr, item_size);
    }

}

void ht_v2::hash_table::swap_hash_t_objs(
    ht_v2::hash_table &obj1, 
    ht_v2::hash_table &obj2
) {
    
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

ht_v2::hash_table & ht_v2::hash_table::operator=(
    const ht_v2::hash_table &copy_ob
) {

    ht_v2::hash_table val_obj(copy_ob);
    swap_hash_t_objs(*this, val_obj);
    return *this;

}


ht_v2::hash_table::hash_table(
    ht_v2::hash_table &&move_ob) 

    : base_capacity     { move_ob.base_capacity }
    , capacity          { move_ob.capacity }
    , item_size         { move_ob.item_size }
    , count             { move_ob.count }
    , scaling_factor    { move_ob.scaling_factor }
    , items             { move_ob.items } {

    move_ob.items = nullptr;
    move_ob.base_capacity = 0;
    move_ob.capacity = 0;
    move_ob.item_size = 0;
    move_ob.count = 0;
    move_ob.scaling_factor = 0;

}

ht_v2::hash_table & ht_v2::hash_table::operator=(
    ht_v2::hash_table &&move_ob) {

    if(this != &move_ob) {
        if(items) {
            operator delete(items[0].val_ptr);
            delete items;
        }   
        items = move_ob.items;
        base_capacity = move_ob.base_capacity;
        capacity = move_ob.capacity;
        item_size = move_ob.item_size;
        count = move_ob.count;
        scaling_factor = move_ob.scaling_factor;
        move_ob.items = nullptr;
        move_ob.base_capacity = 0;
        move_ob.capacity = 0;
        move_ob.item_size = 0;
        move_ob.count = 0;
        move_ob.scaling_factor = 0;
    }
    return *this;

}

ht_v2::hash_table::~hash_table() {

    if(items) {
        operator delete(items[0].val_ptr);
        delete items;
    }

}

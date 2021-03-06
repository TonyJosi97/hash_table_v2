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
#include <time.h>

#define  __HT_DEBUG_OP 

#ifdef  __HT_DEBUG_OP 
    #include <iostream>
    #define     _ht_DEBUG_OP(_str__)    std::cout<<_str__;
#else
    #define     _ht_DEBUG_OP(_str__)
#endif
                                
#include "../inc/hash_table_v2.hpp"
#include "../inc/hash_table_util.hpp"

constexpr size_t SCALE_UP_THRESHOLD     {60};
constexpr size_t SCALE_DOWN_THRESHOLD   {20};

ht_v2::hash_table::hash_table(
    size_t      base_capacity, 
    size_t      item_size) 

    : base_capacity     { base_capacity }
    , capacity          { base_capacity }
    , item_size         { item_size }
    , count             { 0 }
    , scaling_factor    { 0 }
    , items             { capacity ? new struct _ght_item[capacity] : 0 } {

    _ht_DEBUG_OP("Public normal cons. "<<this<<"\n");

    void *_t_mem = operator new(capacity * item_size);
    for(unsigned long i = 0; i < capacity; ++i) {
        items[i].is_active = false;
        items[i].val_ptr = static_cast<char*>(_t_mem) + item_size * i;
    }

}

ht_v2::hash_table::hash_table(
    size_t      base_capacity, 
    size_t      capacity, 
    size_t      item_size,
    int         scaling_factor) 

    : base_capacity     { base_capacity }
    , capacity          { capacity }
    , item_size         { item_size }
    , count             { 0 }
    , scaling_factor    { scaling_factor }
    , items             { capacity ? new struct _ght_item[capacity] : 0 } {

    _ht_DEBUG_OP("Private normal cons. "<<this<<"\n");

    void *_t_mem = operator new(capacity * item_size);
    for(unsigned long i = 0; i < capacity; ++i) {
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

    _ht_DEBUG_OP("Copy cons. "<<this<<"\n");

    void *_t_mem = operator new(capacity * item_size);
    for(unsigned long i = 0; i < capacity; ++i) {
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

}

ht_v2::hash_table & ht_v2::hash_table::operator=(
    const ht_v2::hash_table &copy_ob
) {

    _ht_DEBUG_OP("Copy assign. "<<this<<"\n");

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

    _ht_DEBUG_OP("Move cons. "<<this<<"\n");

    move_ob.items = nullptr;

}

ht_v2::hash_table & ht_v2::hash_table::operator=(
    ht_v2::hash_table &&move_ob) {

    _ht_DEBUG_OP("Move assign. "<<this<<"\n");

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

    }
    return *this;

}

ht_v2::hash_table::~hash_table() {

    _ht_DEBUG_OP("Destructor "<<this<<"\n");

    if(items) {
        operator delete(items[0].val_ptr);
        delete items;
    }

}

ht_v2::ht_ret_status_t ht_v2::hash_table::ht_insert(
    unsigned long key, 
    void *val_ptr
    ) {

    size_t ht_density = (count * 100) / capacity;
    if(ht_density > SCALE_UP_THRESHOLD) {

        *this = __ht_core_util_resize(capacity * 2); 
        /*                -- N O T E --

            *this = std::move(__ht_core_util_resize(capacity * 2)); 

            moving a temporary object
            prevents copy elision [-Wpessimizing-move] 
        */
        
        scaling_factor += 1;

    }

    size_t prev_index;
    if(ht_find(key, prev_index) == 0) 
        return HT_KEY_ALRDY_EXISTS;

    unsigned int chain_len = 0;
    size_t item_index = __ht_core_util_get_hash(key, capacity, chain_len);

    while((items[item_index].is_active) != false) {
        ++chain_len;
        if(chain_len == (capacity - 1))
            throw "Cyclic check";

        item_index++;
        item_index = __ht_core_util_get_hash(item_index, capacity, chain_len);
    }

    try  {
        items[item_index].is_active = true;
        items[item_index].key = key;
        memcpy(items[item_index].val_ptr, val_ptr, item_size);
    }
    catch(...) {
        throw "Insertion Failed";
    }

    count += 1;
    
    return HT_SUCCESS;
}

ht_v2::ht_ret_status_t ht_v2::hash_table::ht_find(
    unsigned long key, 
    size_t &indx
) {


    unsigned int chain_len = 0;
    size_t item_index = __ht_core_util_get_hash(key, capacity, chain_len);

    while((items[item_index].is_active == true) && (items[item_index].key != key)) {

        ++chain_len;
        if(chain_len == (capacity - 1))
            return HT_ITEM_NOT_FOUND;

        item_index++;
        item_index = __ht_core_util_get_hash(item_index, capacity, chain_len);

    }

    if(items[item_index].is_active == true) {
        indx = item_index;
        return HT_SUCCESS;
    }

    return HT_ITEM_NOT_FOUND;

}

ht_v2::ht_ret_status_t ht_v2::hash_table::ht_get(
    unsigned long key, 
    void *ret_val_ptr
) { 

    size_t item_index;
    ht_ret_status_t ret_code;

    if((ret_code = ht_find(key, item_index)) != HT_SUCCESS)
        return ret_code;

    if(!memcpy(ret_val_ptr, items[item_index].val_ptr, item_size)) {
        throw "memcpy() Failed";
    }
    return HT_SUCCESS;
}



ht_v2::ht_ret_status_t ht_v2::hash_table::ht_delete(
    unsigned long key
) { 

    unsigned long ht_density = (count * 100) / capacity;

    if((scaling_factor > 0) && (ht_density < SCALE_DOWN_THRESHOLD)) {

        *this = __ht_core_util_resize(capacity / 2); 
        /*                -- N O T E --

            *this = std::move(__ht_core_util_resize(capacity / 2)); 

            moving a temporary object
            prevents copy elision [-Wpessimizing-move] 
        */

        scaling_factor -= 1;
    }

    bool item_found = false;

    if(count > 0) {

        unsigned int chain_len = 0;
        ht_ret_status_t ret_code;
        size_t item_index = __ht_core_util_get_hash(key, capacity, chain_len);

        while(items[item_index].is_active == true) {

            if(item_found == true) {
                count -= 1;
                items[item_index].is_active = false;
                if((ret_code = ht_insert(items[item_index].key, items[item_index].val_ptr)) != HT_SUCCESS) {
                    count += 1;
                    return HT_FAIL;
                }
            }

            if(items[item_index].key == key) {
                items[item_index].is_active = false;
                item_found = true;
            }

            ++chain_len;
            if(chain_len == (capacity - 1))
                return HT_ITEM_NOT_FOUND;
       
            item_index++;
            item_index = __ht_core_util_get_hash(item_index, capacity, chain_len);

        }
    }
    else
        return HT_EMPTY;

    if(item_found == true) {
        count -= 1;
        return HT_SUCCESS;
    }
    else 
        return HT_FAIL;

}


unsigned long ht_v2::hash_table::ht_generate_key() {

    struct tm * timeinfo;
    time_t now = time(0);
    timeinfo = localtime(&now);

    unsigned long min_int = static_cast<unsigned long>(timeinfo->tm_min);
    unsigned long nanosec_val = get_time_in_nanosec();
    nanosec_val = nanosec_val & 0x00FFFFFFFFFFFFFF;
    nanosec_val += ((min_int & 0xFF) << 56);

    return nanosec_val;

} 


ht_v2::hash_table ht_v2::hash_table::__ht_core_util_resize(
    size_t size_estimate
) { 
    
    _ht_DEBUG_OP("Resize\n");

    size_t new_size = get_next_prime(size_estimate);
    hash_table new_ht(base_capacity, new_size, item_size, scaling_factor);

    if(items) {
        for(size_t i = 0; i < capacity; i++) 
            if(items[i].is_active == true) {
                if(new_ht.ht_insert(items[i].key, items[i].val_ptr) != HT_SUCCESS)
                    {}
            }
    }

    return new_ht;
}


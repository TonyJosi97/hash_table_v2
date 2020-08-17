#include "../inc/hash_table_v2.hpp"

ht_v2::hash_table::hash_table(
    size_t base_capacity, 
    size_t capacity, 
    size_t item_size, 
    size_t count, 
    int scaling_factor) 
    : base_capacity{ base_capacity }
    , capacity{ capacity }
    , item_size{ item_size }
    , count{ count }
    , scaling_factor{ scaling_factor }
    , items{ new struct _ght_item[capacity] } {

        void *_t_mem = operator new(capacity * item_size);
        for(int i = 0; i < capacity; ++i) {
            items[i].is_active = false;
            items[i].val_ptr = _t_mem + item_size * i;
        }

    }
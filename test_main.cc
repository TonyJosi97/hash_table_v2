#include <iostream>
#include <time.h>
#include "inc/hash_table_v2.hpp"

using namespace ht_v2;
//#define RAND_GEN(N)                     (int)((double)rand() / ((double)RAND_MAX + 1) * N)


typedef struct _test_main {
    int x;
    float y;
} test_main_t;

constexpr int max_tests {32500};
 
int main() {

    hash_table basic_test_obj(1931, sizeof(test_main_t));
    //unsigned long val = basic_test_obj.ht_generate_key();
    test_main_t temp;
    unsigned long key_holder[max_tests];

    for(unsigned int i = 0; i < max_tests; ++i) {
        temp.x = (655363463 * (i + 1)) % 1931;
        temp.y = (623434552 * (i + 1)) % 1931;
        key_holder[i] = basic_test_obj.ht_generate_key();
        basic_test_obj.ht_insert(key_holder[i], &temp);
        //std::cout<<temp.x<<" "<<temp.y<<" "<<key_holder[i]<<std::endl;
    }

    std::cout<<"--------------\n";

    for(int i = 0; i < max_tests; ++i) {
        basic_test_obj.ht_get(key_holder[i], &temp);
        basic_test_obj.ht_delete(key_holder[i]);
        //std::cout<<temp.x<<" "<<temp.y<<" "<<key_holder[i]<<std::endl;
    }
}


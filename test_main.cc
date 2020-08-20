#include <iostream>
#include "inc/hash_table_v2.hpp"

//using namespace ht_v2;

typedef struct _test_main {
    int x;
    float y;
} test_main_t;

 
int main() {
    ht_v2::hash_table basic_test_obj(1931, 1931, sizeof(test_main_t), 0, 0);
    unsigned long val = basic_test_obj.ht_generate_key();
    std::cout<<val<<":  Hello\n";
}


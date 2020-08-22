#include <iostream>
#include <time.h>
#include <stdio.h>
#include "inc/hash_table_v2.hpp"

using namespace ht_v2;

typedef struct _test_main {
    int x;
    float y;
} test_main_t;

constexpr int max_tests {3250};

double master_tester() {
    //unsigned long val = basic_test_obj.ht_generate_key();
    test_main_t temp;
    unsigned long key_holder[max_tests];

    hash_table basic_test_obj(1931, sizeof(test_main_t));

    for(unsigned int i = 0; i < max_tests; ++i) {
        temp.x = (655363463 * (i + 1)) % 1931;
        temp.y = (623434552 * (i + 1)) % 1931;
        key_holder[i] = basic_test_obj.ht_generate_key();
        basic_test_obj.ht_insert(key_holder[i], &temp);
        //std::cout<<"Insert "<<key_holder[i]<<std::endl;
        std::printf("Insert %ld\n", key_holder[i]);
        //std::cout<<temp.x<<" "<<temp.y<<" "<<key_holder[i]<<std::endl;
    }

    for(int i = 0; i < max_tests; ++i) {
        basic_test_obj.ht_get(key_holder[i], &temp);
        //std::cout<<"Got "<<key_holder[i]<<temp.x<<temp.y<<std::endl;
        std::printf("Got %ld %d %f\n", key_holder[i], temp.x, temp.y);
        basic_test_obj.ht_delete(key_holder[i]);
        //std::cout<<"Delete "<<key_holder[i]<<std::endl;
        std::printf("Delete %ld\n", key_holder[i]);
        //std::cout<<temp.x<<" "<<temp.y<<" "<<key_holder[i]<<std::endl;
    }

    return 0;
}
 
int main() {

    const int t_cases = 100;
    std::clock_t begin = std::clock();
    for(int i = 0 ; i < t_cases; ++i) {
        master_tester();
    }
    std::clock_t end = std::clock();
    float val = ((end - begin) / ((float)CLOCKS_PER_SEC));
    //std::cout<<end<<" "<<begin<<" "<<CLOCKS_PER_SEC<<" "<<val<<std::endl; 
    std::printf("Delay: %f\n", val/t_cases);

}


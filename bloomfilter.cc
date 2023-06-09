//
// Created by yichen_X on 2023/4/2.
//

#include <cstring>
#include "bloomfilter.h"

bloomfilter::~bloomfilter() {
}

void bloomfilter::insert(const uint64_t key) {
    unsigned int hash[4] = {0};
    MurmurHash3_x64_128(&key, sizeof(key), 1, &hash);

    for(int i = 0; i < hash_num; ++i){
        uint64_t hash_value = hash[i] % bitset_size;
        bitset.set(hash_value);
    }
}

bool bloomfilter::find(const uint64_t key) {
    unsigned int hash[4] = {0};
    MurmurHash3_x64_128(&key, sizeof(key), 1, &hash);
    for(int i = 0; i < hash_num; ++i){
        uint64_t hash_value = hash[i] % bitset_size;
        if(bitset.test(hash_value) == 0) return false;
    }
    return true;
}

void bloomfilter::saveBloomFilter(char *buf) {
    memcpy(buf, (char*)&bitset, BLOOMFILTER_SIZE/8);
}
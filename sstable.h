//
// Created by yichen_X on 2023/4/1.
//

#ifndef LSM_KV_SSTABLE_H
#define LSM_KV_SSTABLE_H

#include <vector>
#include <iostream>
#include "bloomfilter.h"

struct index_item{
private:
    uint64_t key;
    uint32_t offset;
public:
    index_item(const uint64_t k, const uint32_t of): key(k), offset(of){}
    uint64_t get_key() const{return key;}
    uint32_t get_offset() const{return offset;}
};

class sstable_cache{
private:
    /* tag */
    uint64_t tag;
    /* Header */
    uint64_t time_stamp;
    uint64_t pair_num;
    uint64_t min_key, max_key;

public:
    /* BloomFilter */
    bloomfilter* bloomfilter;

    /* Index */
    std::vector<index_item> Indexs;

    sstable_cache();

    uint64_t get_tag() const{return tag;}
    void set_tag(const uint64_t t){tag = t;}
    uint64_t get_timestamp() const{return time_stamp;}
    void set_timestamp(const uint64_t ts){time_stamp = ts;}
    void set_num(const uint64_t n){pair_num = n;}
    void set_minkey(const uint64_t m_k){min_key = m_k;}
    void set_maxkey(const uint64_t m_k){max_key = m_k;}
    uint64_t get_min_key() const{return min_key;}
    uint64_t get_max_key() const{return max_key;}
    void insert_key_to_bloomfilter(const uint64_t key) const{bloomfilter->insert(key);}
    bool find_key_in_bloomfilter(const uint64_t key) const{return bloomfilter->find(key);}

    index_item* find_key_in_indexs(uint64_t key, uint32_t& value_size);
    bool is_in_range(uint64_t& key) const;
    ~sstable_cache();
};

#endif //LSM_KV_SSTABLE_H

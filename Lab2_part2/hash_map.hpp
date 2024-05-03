#ifndef HASH_MAP_HPP
#define HASH_MAP_HPP
#include <algorithm> 
#include "hash_map.h"
#include <iostream>

// constructor
template <typename K, typename V>
hash_map<K, V>::hash_map(size_t capacity, float upper_load_factor, float lower_load_factor) {
    this->_size = 0;
    this->_capacity = capacity;
    this->_head = new hash_list<K,V>[capacity];
    this ->_upper_load_factor = upper_load_factor;
    this ->_lower_load_factor = lower_load_factor;
}
template <typename K, typename V>
hash_map<K, V>::hash_map(const hash_map &other){
    this->_size = 0;
    this->_capacity = other._capacity;
    this->_head = new hash_list<K,V>[this->_capacity];
    for(size_t i = 0; i < this->_capacity; i++){
        _head[i] = other._head[i];
    }
    this->_size = other._size;
    this ->_upper_load_factor = other._upper_load_factor;
    this ->_lower_load_factor = other._lower_load_factor;

}
template <typename K, typename V>
hash_map<K,V> &hash_map<K,V>::operator=(const hash_map<K,V> &other){
    if(this == &other){
        return *this;
    }
    this->~hash_map();

    this->_size = other._size;
    this ->_upper_load_factor = other._upper_load_factor;
    this ->_lower_load_factor = other._lower_load_factor;
    this->_capacity = other._capacity;
    this->_head = new hash_list<K,V>[this->_capacity];
    for(size_t i = 0; i < this->_capacity; i++){
        _head[i] = other._head[i];
    }
    return *this;

}

template <typename K, typename V>
size_t hash_map<K,V>::get_capacity() const{
    return this->_capacity;
}
template <typename K, typename V>
size_t hash_map<K,V>::get_size() const{
    return _size;
}

template <typename K, typename V>
void hash_map<K,V>::get_all_keys(K *keys){
    int key_index = 0;
    for(size_t i = 0; i < this->_capacity; i++){
        hash_list<K,V>& list = _head[i];
        list.reset_iter();

        /** We want to iterate over all nodes, so keep iterating until we're at the end */
        while (!list.iter_at_end())
        {
            /** Get pointers to key/value pairs */
            std::optional<std::pair<const K *, V *>> node_values = list.get_iter_value();
            if(node_values.has_value()){
                keys[key_index] = *(node_values.value().first);
                key_index++;
            }

            /** Go to the next element */
            list.increment_iter();
        }
    }

}
template <typename K, typename V>
void hash_map<K,V>::get_bucket_sizes(size_t *buckets){
    for(size_t i = 0; i < this->_capacity; i++){
        hash_list<K,V>& list = _head[i];
        buckets[i] = list.get_size();
        /** We want to iterate over all nodes, so keep iterating until we're at the end */
    }
}
template <typename K, typename V>
std::optional<V> hash_map<K,V>::get_value(K key) const{
    size_t index = this->_hash(key) % this->_capacity;
    hash_list<K,V>& list = _head[index];
    return list.get_value(key);
}

template <typename K, typename V>
void hash_map<K,V>::insert(K key, V value){
    size_t index = this->_hash(key) % this->_capacity;
    hash_list<K,V>& list = _head[index];

    // size_t pre_size = list.get_size();
    int ins = list.insert(key, value);
    // std::cout << "pre " << pre_size << "post " << list.get_size() << std::endl;

    if(ins){
        this->_size += 1;
    }
    hash_map<K,V>::need_to_rehash();
}

template <typename K, typename V>
bool hash_map<K,V>::remove(K key){
    int index = this->_hash(key) % this->_capacity;
    hash_list<K,V>& list = _head[index];
    int rem = list.remove(key);
    if(rem){
        this->_size -= 1;
    }
    hash_map<K,V>::need_to_rehash();
    return rem;
}

template <typename K, typename V>
void hash_map<K,V>::get_all_sorted_keys(K *keys){

    hash_map<K,V>::get_all_keys(keys);
    // if(this->_size > 1){
    std::sort(keys, keys + _size); 

    // }
    
}


template <typename K, typename V>
bool hash_map<K,V>::need_to_rehash(){

    if(this-> _size > (this->_upper_load_factor * this->_capacity)){

        // std::cout << _capacity<< " in rehash increase" << std::endl;
        for(int i = 0; i < 3; i++){
            // std::cout << _capacity << " new " <<_capacities[i]<< " in rehash increase" << std::endl;

            if(this-> _capacity < _capacities[i]){
                hash_map<K,V>::rehash(_capacities[i]);
                return 1; 
            }
            // return 0;
        }
        
    }
    if (this-> _size < (this->_lower_load_factor * this->_capacity)){
        // if(this-> _capacity > hash_map<K, V>::_capacities[0]){
        //     hash_map<K,V>::rehash(_capacities[0]);
        // }
        for(int i = 2; i >= 0 ; i--){
            if(this-> _capacity > _capacities[i]){
                hash_map<K,V>::rehash(_capacities[i]);
                return 1;
            }
            // return 0;
        }

        
    }

    
    return 0;
}

template <typename K, typename V>
void hash_map<K,V>::rehash(size_t capacity){

    // new head array to replace old head
    hash_list<K, V>* new_head_array = new hash_list<K, V>[capacity];
    // std::cout << _size<< " in rehash increase" << std::endl;

    for(size_t i = 0; i< this->_capacity; i++){
        // get orignal head array
        hash_list<K, V>& old_head_array = this->_head[i];

        // get list back to head
        old_head_array.reset_iter();
        while(old_head_array.iter_at_end() == false){
            std::optional<std::pair<const K *, V *>> node_values = old_head_array.get_iter_value();   
            if(node_values.has_value() == true){
                K new_key = *(node_values.value().first);
                V new_value = *(node_values.value().second);
                size_t bucket = _hash(new_key) % capacity;
                new_head_array[bucket].insert(new_key, new_value);
            } 
            old_head_array.increment_iter();
        }
    }

    delete[] this->_head;
    this->_head = new_head_array;
    this->_capacity = capacity;
    // std::cout << _size<< " in rehash increase" << std::endl;
    



}


template <typename K, typename V>
hash_map<K,V>::~hash_map(){
    delete[] this->_head;
}

#endif


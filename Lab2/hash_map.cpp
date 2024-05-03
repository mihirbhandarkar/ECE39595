#include "hash_map.h"
#include <iostream>

// constructor
hash_map::hash_map(size_t capacity) {
    this->_size = 0;
    this->_capacity = capacity;
    this->_head = new hash_list[capacity];
}
hash_map::hash_map(const hash_map &other){
    this->_size = 0;
    this->_capacity = other._capacity;
    this->_head = new hash_list[this->_capacity];
    for(int i = 0; i < this->_capacity; i++){
        _head[i] = other._head[i];
    }
    this->_size = other._size;

}
hash_map &hash_map::operator=(const hash_map &other){
    if(this == &other){
        return *this;
    }
    this->~hash_map();

    this->_size = other._size;
    this->_capacity = other._capacity;
    this->_head = new hash_list[this->_capacity];
    for(int i = 0; i < this->_capacity; i++){
        _head[i] = other._head[i];
    }
    return *this;

}


size_t hash_map::get_capacity() const{
    return this->_capacity;
}

size_t hash_map::get_size() const{
    return _size;
}

void hash_map::get_all_keys(int *keys){
    int key_index = 0;
    for(int i = 0; i < this->_capacity; i++){
        hash_list& list = _head[i];
        list.reset_iter();

        /** We want to iterate over all nodes, so keep iterating until we're at the end */
        while (!list.iter_at_end())
        {
            /** Get pointers to key/value pairs */
            std::optional<std::pair<const int *, float *>> node_values = list.get_iter_value();
            if(node_values.has_value()){
                keys[key_index] = *(node_values.value().first);
                key_index++;
            }

            /** Go to the next element */
            list.increment_iter();
        }
    }

}

void hash_map::get_bucket_sizes(size_t *buckets){
    for(int i = 0; i < this->_capacity; i++){
        hash_list& list = _head[i];
        buckets[i] = list.get_size();
        /** We want to iterate over all nodes, so keep iterating until we're at the end */
    }
}

std::optional<float> hash_map::get_value(int key) const{
    int index = std::abs(key) % this->_capacity;
    hash_list& list = _head[index];
    return list.get_value(key);
}
void hash_map::insert(int key, float value){
    int index = std::abs(key) % this->_capacity;
    hash_list& list = _head[index];

    size_t pre_size = list.get_size();
    int ins = list.insert(key, value);
    // std::cout << "pre " << pre_size << "post " << list.get_size() << std::endl;

    if(ins){
        this->_size += 1;
    }

    

}
bool hash_map::remove(int key){
    int index = std::abs(key) % this->_capacity;
    hash_list& list = _head[index];
    int rem = list.remove(key);
    if(rem){
        this->_size -= 1;
    }
    return rem;
}
hash_map::~hash_map(){
    delete[] this->_head;
}



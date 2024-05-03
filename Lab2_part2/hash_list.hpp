#ifndef HASH_LIST_HPP
#define HASH_LIST_HPP

#include "hash_list.h"
#include <iostream>

// constructor
template <typename K, typename V>
hash_list<K,V>::hash_list() {
    size = 0;
    head = NULL;
    iter_ptr = NULL;

}

/**-----------------------------------------------------------------------------------
 * START Part 1
 *------------------------------------------------------------------------------------*/
template <typename K, typename V>
bool hash_list<K,V>::insert(K key, V value) {
    if(this->size == 0){
        // node* new_node = new node;
        node<K,V>* new_node = new node<K,V>;
        new_node -> key = key;
        new_node -> value = value;
        new_node -> next = this->head;
        this-> head = new_node;
        this-> size += 1;
        return true;
    }

    node<K,V>* temp = this->head;
    while(temp != NULL){
        if(temp-> key == key){
            temp -> value = value;
            return false;
        }
        temp = temp -> next;
    }
    node<K,V>* new_node = new node<K,V>;
    new_node -> key = key;
    new_node -> value = value;
    new_node -> next = this->head;
    this-> head = new_node;
    this-> size += 1;
    return true;
}
template <typename K, typename V>
std::optional<V> hash_list<K,V>::get_value(K key) const { 
    node<K,V>* temp = this -> head;
    while(temp != NULL){
        if(temp -> key == key){
            return temp -> value;
        }
        temp = temp -> next;
    }
    return std::nullopt; }
template <typename K, typename V>
bool hash_list<K,V>::remove(K key) { 
    node<K,V>* prev = this->head;
    if(prev == NULL){
        return false;
    }

    if(prev -> key == key){
        this ->head = prev->next;
        this->size = this->size - 1;
        delete prev;
        return true;
    }
    node<K,V>* curr = prev -> next;


    while(curr != NULL){
        if( curr-> key == key){
            prev -> next = curr -> next;
            delete curr;
            this->size = this->size - 1;
            return true;
        }
        prev = curr;
        curr = curr -> next;
    }
    return false; 
    // node* prev = this->head;
    // node* curr = (this->head) -> next;
    // // if(prev -> key == key){
    // //     this ->head = temp->next;
    // //     delete temp;
    // //     return true;

    // // }

    // while(curr != NULL){
    //     if( curr-> key == key){
    //         prev -> next = curr -> next;
    //         delete curr;
    //         this->size = this->size - 1;
    //         return true;
    //     }
    //     prev = curr;
    //     curr = curr -> next;
    // }
    // return false; 

}

// destructor
template <typename K, typename V>
size_t hash_list<K,V>::get_size() const { return (this-> size); }

template <typename K, typename V>
hash_list<K,V>::~hash_list() {
    if(this->size != 0){
        while(this->head != NULL){
            node<K,V>* temp = this->head;
            this->head = (this->head) -> next;
            this->size = this -> size - 1;
            delete temp;
        }
    }
}

/**-----------------------------------------------------------------------------------
 * END Part 1
 *------------------------------------------------------------------------------------*/


/**-----------------------------------------------------------------------------------
 * START Part 2
 *------------------------------------------------------------------------------------*/
template <typename K, typename V>
hash_list<K,V>::hash_list(const hash_list &other) {
    this->size = 0;
    this->head = NULL;
    this->iter_ptr = other.iter_ptr;

    node<K,V>* temp = other.head;

    while(temp != NULL){
        this->insert(temp->key,temp->value);
        temp = temp -> next;
    }

}

template <typename K, typename V>
hash_list<K,V> &hash_list<K,V>::operator=(const hash_list &other) { 
    // the hash_list has been created already
    if(this == &other){
        return *this;

    }
    // call the deconstructor to remove any and all nodes that was previously there
    this->~hash_list<K,V>();

    // basically the deconstructor

    // while(this->head != NULL){
    //     node* temp = this->head;
    //     this->head = (this->head) -> next;
    //     this->size = this -> size - 1;
    //     delete temp;
    // }
    
    //
    this->size = 0;
    this->head = NULL;
    this->iter_ptr = other.iter_ptr;

    node<K,V>* temp = other.head;

    while(temp != NULL){
        this->insert(temp->key,temp->value);
        temp = temp -> next;
    }        
    
    return *this; 
}

template <typename K, typename V>
void hash_list<K,V>::reset_iter() {
    if(this->size == 0){
        this->iter_ptr = NULL;
    }
    else{
        this->iter_ptr = this->head;
    }
    
}

template <typename K, typename V>
void hash_list<K,V>::increment_iter() {
    if(this->iter_ptr){
        this->iter_ptr = (this->iter_ptr) -> next;
    }
}

template <typename K, typename V>
std::optional<std::pair<const K *, V *>> hash_list<K,V>::get_iter_value() { 
    if(this->iter_ptr){
        std::pair<int *, float *> iter_pair;
        iter_pair = std::make_pair(&((this->iter_ptr) -> key), &((this->iter_ptr) -> value));

        // iter_pair.first = (this->iter_ptr) -> key;
        // iter_pair.second = (this->iter_ptr) -> value;

        //HELP please
        return iter_pair;
    }
    
    // make_pair() -function
    return std::nullopt;     
}

template <typename K, typename V>
bool hash_list<K,V>::iter_at_end() { 
    if(this->iter_ptr){
        return false;
    }
    
    
    return true; 
}
/**-----------------------------------------------------------------------------------
 * END Part 2
 *------------------------------------------------------------------------------------*/
#endif

#include "hash_list.h"
#include <iostream>

// constructor
hash_list::hash_list() {
    size = 0;
    head = NULL;
    iter_ptr = NULL;

}

/**-----------------------------------------------------------------------------------
 * START Part 1
 *------------------------------------------------------------------------------------*/
bool hash_list::insert(int key, float value) {
    if(this->size == 0){
        // node* new_node = new node;
        node* new_node = new node;
        new_node -> key = key;
        new_node -> value = value;
        new_node -> next = this->head;
        this-> head = new_node;
        this-> size += 1;
        return true;
    }

    node* temp = this->head;
    while(temp != NULL){
        if(temp-> key == key){
            temp -> value = value;
            return false;
        }
        temp = temp -> next;
    }
    node* new_node = new node;
    new_node -> key = key;
    new_node -> value = value;
    new_node -> next = this->head;
    this-> head = new_node;
    this-> size += 1;
    return true;
}

std::optional<float> hash_list::get_value(int key) const { 
    node* temp = this -> head;
    while(temp != NULL){
        if(temp -> key == key){
            return temp -> value;
        }
        temp = temp -> next;
    }
    return std::nullopt; }

bool hash_list::remove(int key) { 
    node* prev = this->head;
    if(prev == NULL){
        return false;
    }

    if(prev -> key == key){
        this ->head = prev->next;
        this->size = this->size - 1;
        delete prev;
        return true;
    }
    node* curr = prev -> next;


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

size_t hash_list::get_size() const { return (this-> size); }

// destructor
hash_list::~hash_list() {
    if(this->size != 0){
        while(this->head != NULL){
            node* temp = this->head;
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

hash_list::hash_list(const hash_list &other) {
    this->size = 0;
    this->head = NULL;
    this->iter_ptr = other.iter_ptr;

    node* temp = other.head;

    while(temp != NULL){
        this->insert(temp->key,temp->value);
        temp = temp -> next;
    }

}
    
hash_list &hash_list::operator=(const hash_list &other) { 
    // the hash_list has been created already
    if(this == &other){
        return *this;

    }
    // call the deconstructor to remove any and all nodes that was previously there
    this->~hash_list();

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

    node* temp = other.head;

    while(temp != NULL){
        this->insert(temp->key,temp->value);
        temp = temp -> next;
    }        
    
    return *this; 
}

void hash_list::reset_iter() {
    if(this->size == 0){
        this->iter_ptr = NULL;
    }
    else{
        this->iter_ptr = this->head;
    }
    
}


void hash_list::increment_iter() {
    if(this->iter_ptr){
        this->iter_ptr = (this->iter_ptr) -> next;
    }
}


std::optional<std::pair<const int *, float *>> hash_list::get_iter_value() { 
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


bool hash_list::iter_at_end() { 
    if(this->iter_ptr){
        return false;
    }
    
    
    return true; 
}
/**-----------------------------------------------------------------------------------
 * END Part 2
 *------------------------------------------------------------------------------------*/

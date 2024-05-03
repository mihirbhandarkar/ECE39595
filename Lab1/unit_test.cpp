#include <iostream>
#include "hash_list.h"

using std::cout;
using std::endl;

// function prototypes
void t_constructor(void);
void t_iter_multiple_nodes(void);
void t_copy_constructor_1(void);
void t_copy_constructor_2(void);


// test harness
int unittest_main(){
  // invoke unit tests as separate functions
  t_constructor();
  t_iter_multiple_nodes();
  t_copy_constructor_1();
  t_copy_constructor_2();

  return 0;
}

void t_constructor(void) {
  // arrange
  hash_list list;

  // act
  // in this simple case there is nothing more to do

  // assert
  if(list.get_size() != 0) {
    cout << "t_constructor: invalid size" << endl;
    // generally for unit testing don't abort execution
    // so the rest of your test suite can continue      
  }
}

void t_iter_multiple_nodes(void) {
  // --- arrange ---
  // create empty list; populate with values; reset iterator
  hash_list list;
  list.insert(7,70);
  list.insert(8,80);
  list.insert(9,90);
  list.reset_iter();

  // --- act ---
  // iterate through the loop
  while (!list.iter_at_end()) {
    // Get pointers to key/value pairs
    std::optional<std::pair<const int *, float *>> node_value = list.get_iter_value();
        
    // output node
    cout << "key: " << *node_value.value().first
	 << ", value: " << *node_value.value().second << endl;

    // go to next element
    list.increment_iter();
  }
  // --- assert ---
  // in this example, verification is by visual inspection because 
  // the order nodes are printed depends on your implementation
}

void t_copy_constructor_1(void) {
  // arrange
  hash_list list1;

  list1.insert(7,70);
  list1.insert(8,80);
  list1.insert(9,90);

  hash_list list_copy(list1);

  if(list1.get_size() != list_copy.get_size()){
        cout << "t_copy_constructor: invalid size" << endl;
  }
  list1.reset_iter(); // go back to head

  while (!list1.iter_at_end()) {

    std::optional<std::pair<const int *, float *>> node_value = list1.get_iter_value();
    std::optional<std::pair<const int *, float *>> node_value_copy = list_copy.get_iter_value();
    if((node_value.value().first != node_value_copy.value().first) && (node_value.value().second != node_value_copy.value().second)){
      cout << "t_copy_constructor: invalid key or value" << endl;
    }

    list1.increment_iter();
    list_copy.increment_iter();

  }

}


void t_copy_constructor_2(void) {
  // arrange
  hash_list list1;

  hash_list list_copy(list1);

  if(list1.get_size() != list_copy.get_size()){
    cout << "t_copy_constructor: invalid size" << endl;
  }
  if(list1.get_value(0) != list_copy.get_value(0)){
    cout << "t_copy_constructor: invalid value" << endl;
  }

}
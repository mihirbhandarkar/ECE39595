#include "hash_map.h"
#include "hash_list.h"

void unittestmain();

int test_insert_one(); // insert
int test_insert_same_bucket();
int test_insert_same_value();
int test_insert_many();

int test_retrieve_present(); // get_value
int test_retrieve_not_present();
int test_retrieve_overwritten();

int test_remove_one(); // remove
int test_remove_true(); 
int test_remove_false();

int test_copy_constructor(); // copy

int test_assignment(); // assignment
int test_self_assignment();

int test_bucket_size_three(); // get_bucket_sizes

int test_get_keys_three(); // get_all_keys
int test_get_sorted_keys();
void test_increase_bucket();

// int test_get_sorted_keys(); //get_sorted_keys 
#include "unittest.h"
#include <iostream>
#include <string>
using std::endl;
using std::cout;

void unittestmain() {
    int retval = 0;

    retval += test_insert_one(); // insert
    retval += test_insert_same_bucket();
    retval += test_insert_same_value();
    retval += test_insert_many();

    retval += test_retrieve_present(); // get_value
    retval += test_retrieve_not_present();
    retval += test_retrieve_overwritten();

    retval += test_remove_one(); // remove
    retval += test_remove_true(); 
    retval += test_remove_false();

    retval += test_copy_constructor(); // copy

    retval += test_assignment(); // assignment
    retval += test_self_assignment();

    retval += test_bucket_size_three(); // get_bucket_sizes

    retval += test_get_keys_three(); // get_all_keys
    retval += test_get_sorted_keys(); // get all sorted keys
    cout << "TOTAL UNIT TEST ERRORS: " << retval << endl;

    test_increase_bucket();
}

int test_insert_one() { // insert //DONE
    int retval = 0;
    std::string METHOD = "test_insert_one";
    // Arrange
    hash_map<int, float> map(3, 1, 0.95);

    // Act
    map.insert(8, 1); // Expecting this to be inserted into 8 % 3 = index 2

    // Assert
    //map.print_map();
    if (map.get_size() == 1) {
        cout << METHOD << " - Test Passed (Size)" << endl;
    }
    else {
        retval++;
        cout << METHOD << " - Incorrect _size, should be 1 but is " << map.get_size() << endl;
    }
    return retval;
}
int test_insert_same_bucket() { 
    int retval = 0;
    std::string METHOD = "test_insert_same_bucket";
    // Arrange
    hash_map<int, float> map(3, 1, 0.95);

    // Act
    map.insert(8, 1); 
    map.insert(2, 5);

    // Assert
    //map.print_map();
    if (map.get_size() == 2) {
        cout << METHOD << " - Test Passed (Size)" << endl; //DONE
    }
    else {
        retval++;
        cout << METHOD << " - Incorrect _size, should be 2 but is " << map.get_size() << endl; 
    }

    size_t buckets [map.get_capacity()];
    map.get_bucket_sizes(buckets);
    if (buckets[2] == 2) {
        cout << METHOD << " - Test Passed (Bucket size)" << endl;
    }
    else {
        retval++;
        cout << METHOD << " - Incorrect bucket size for index 2, should be 2 but is " << buckets[2] << endl;
    }
    return retval;
}
int test_insert_same_value() {
    int retval = 0;
    std::string METHOD = "test_insert_same_value";
    // Arrange
    hash_map<int, float> map(3, 1, 0.95);

    // Act
    map.insert(8, 1); 
    map.insert(8, 5);

    // Assert
    //map.print_map();
    if (map.get_size() == 1) {
        cout << METHOD << " - Test Passed (Size)" << endl;
    }
    else {
        retval++;
        cout << METHOD << " - Incorrect _size, should be 1 but is " << map.get_size() << endl;
    }

    size_t buckets [map.get_capacity()];
    map.get_bucket_sizes(buckets);
    if (buckets[2] == 1) {
        cout << METHOD << " - Test Passed (Bucket size)" << endl;
    }
    else {
        retval++;
        cout << METHOD << " - Incorrect bucket size for index 2, should be 1 but is " << buckets[2] << endl;
    }
    return retval;
}
int test_insert_many() {
    int retval = 0;
    std::string METHOD = "test_insert_many";
    // Arrange
    hash_map<int, float> map(3, 1, 0.95);

    // Act
    map.insert(1, 1); 
    map.insert(1, 5);
    map.insert(3, 2);
    map.insert(2, 1);
    map.insert(6, 4);
    map.insert(4, 23);
    map.insert(6, 23);

    // Assert
    //map.print_map();
    if (map.get_size() == 5) {
        cout << METHOD << " - Test Passed (Size)" << endl;
    }
    else {
        retval++;
        cout << METHOD << " - Incorrect _size, should be 5 but is " << map.get_size() << endl;
    }

    size_t buckets [map.get_capacity()];
    map.get_bucket_sizes(buckets);
    if (buckets[0] == 0) {
        cout << METHOD << " - Test Passed (Bucket size index 0)" << endl;
    }
    else {
        retval++;
        cout << METHOD << " - Incorrect bucket size for index 0, should be 0 but is " << buckets[0] << endl;
    }
    if (buckets[1] == 1) {
        cout << METHOD << " - Test Passed (Bucket size index 1)" << endl;
    }
    else {
        retval++;
        cout << METHOD << " - Incorrect bucket size for index 1, should be 1 but is " << buckets[1] << endl;
    }
    if (buckets[2] == 1) {
        cout << METHOD << " - Test Passed (Bucket size index 2)" << endl;
    }
    else {
        retval++;
        cout << METHOD << " - Incorrect bucket size for index 2, should be 1 but is " << buckets[2] << endl;
    }
    if (buckets[3] == 1) {
        cout << METHOD << " - Test Passed (Bucket size index 3)" << endl;
    }
    else {
        retval++;
        cout << METHOD << " - Incorrect bucket size for index 3, should be 1 but is " << buckets[3] << endl;
    }
    if (buckets[4] == 1) {
        cout << METHOD << " - Test Passed (Bucket size index 4)" << endl;
    }
    else {
        retval++;
        cout << METHOD << " - Incorrect bucket size for index 4, should be 1 but is " << buckets[4] << endl;
    }
    if (buckets[6] == 1) {
        cout << METHOD << " - Test Passed (Bucket size index 6)" << endl;
    }
    else {
        retval++;
        cout << METHOD << " - Incorrect bucket size for index 6, should be 1 but is " << buckets[6] << endl;
    }
    return retval;
}

int test_retrieve_present() { // get_value
    int retval = 0;
    std::string METHOD = "test_retrieve_present";
    // Arrange
    hash_map<int, float> map(3, 1, 0.95);

    // Act
    map.insert(8, 1);
    map.insert(2, 5);
    std::optional<float> val = map.get_value(8);

    // Assert
    //map.print_map();
    if (val.has_value()) {
        cout << METHOD << " - Test Passed (Has value)" << endl;
    }
    else {
        retval++;
        cout << METHOD << " - Incorrect, has no value but should" << endl;
    }
    if (val.value() == 1) {
        cout << METHOD << " - Test Passed (Correct value)" << endl;
    }
    else {
        retval++;
        cout << METHOD << " - Incorrect, value should be 1 but is " << val.value() << endl;
    }
    return retval;
}
int test_retrieve_not_present() {
    int retval = 0;
    std::string METHOD = "test_retrieve_not_present";
    // Arrange
    hash_map<int, float> map(3, 1, 0.95);

    // Act
    map.insert(8, 1);
    map.insert(2, 5);
    std::optional<float> val = map.get_value(5);

    // Assert
    //map.print_map();
    if (!val.has_value()) {
        cout << METHOD << " - Test Passed (Has no value)" << endl;
    }
    else {
        retval++;
        cout << METHOD << " - Incorrect, has value but should not" << endl;
    }
    return retval;
}
int test_retrieve_overwritten() {
    int retval = 0;
    std::string METHOD = "test_retrieve_overwritten";
    // Arrange
    hash_map<int, float> map(5, 1, 0.95);

    // Act
    map.insert(8, 1);
    map.insert(2, 5);
    map.insert(2, 10);
    map.insert(7, 4);
    std::optional<float> val = map.get_value(2);

    // Assert
    //map.print_map();
    if (val.has_value()) {
        cout << METHOD << " - Test Passed (Has value)" << endl;
    }
    else {
        retval++;
        cout << METHOD << " - Incorrect, has no value but should" << endl;
    }
    if (val.value() == 10) {
        cout << METHOD << " - Test Passed (Correct value)" << endl;
    }
    else {
        retval++;
        cout << METHOD << " - Incorrect, value should be 10 but is " << val.value() << endl;
    }
    return retval;
}

int test_remove_one() { // remove
    int retval = 0;
    std::string METHOD = "test_remove_one";
    // Arrange
    hash_map<int, float> map(3, 1, 0.95);

    // Act
    map.insert(8, 1); 
    map.insert(2, 5);
    map.remove(2);

    // Assert
    //map.print_map();
    if (map.get_size() == 1) {
        cout << METHOD << " - Test Passed (Size)" << endl;
    }
    else {
        retval++;
        cout << METHOD << " - Incorrect _size, should be 1 but is " << map.get_size() << endl;
    }

    size_t buckets [map.get_capacity()];
    map.get_bucket_sizes(buckets);
    if (buckets[2] == 1) {
        cout << METHOD << " - Test Passed (Bucket size)" << endl;
    }
    else {
        retval++;
        cout << METHOD << " - Incorrect bucket size for index 2, should be 1 but is " << buckets[2] << endl;
    }
    return retval;
}
int test_remove_true() {
    int retval = 0;
    std::string METHOD = "test_remove_true";
    // Arrange
    hash_map<int, float> map(6, 1, 0.95);

    // Act
    map.insert(5, 1); 
    map.insert(2, 5);
    bool val = map.remove(2);

    // Assert
    //map.print_map();
    if (map.get_size() == 1) {
        cout << METHOD << " - Test Passed (Size)" << endl;
    }
    else {
        retval++;
        cout << METHOD << " - Incorrect _size, should be 1 but is " << map.get_size() << endl;
    }

    size_t buckets [map.get_capacity()];
    map.get_bucket_sizes(buckets);
    if (buckets[2] == 0) {
        cout << METHOD << " - Test Passed (Bucket size)" << endl;
    }
    else {
        retval++;
        cout << METHOD << " - Incorrect bucket size for index 2, should be 0 but is " << buckets[2] << endl;
    }

    if (val == true) {
        cout << METHOD << " - Test Passed (Return value)" << endl;
    }
    else {
        retval++;
        cout << METHOD << " - Incorrect return value for remove, should be true but is false" << endl;
    }
    return retval;
}
int test_remove_false() {
    int retval = 0;
    std::string METHOD = "test_remove_false";
    // Arrange
    hash_map<int, float> map(5, 1, 0.95);

    // Act
    map.insert(5, 1); 
    map.insert(2, 5);
    bool val = map.remove(3);

    // Assert
    //map.print_map();
    if (map.get_size() == 2) {
        cout << METHOD << " - Test Passed (Size)" << endl;
    }
    else {
        retval++;
        cout << METHOD << " - Incorrect _size, should be 2 but is " << map.get_size() << endl;
    }
    if (val == false) {
        cout << METHOD << " - Test Passed (Return value)" << endl;
    }
    else {
        retval++;
        cout << METHOD << " - Incorrect return value for remove, should be false but is true" << endl;
    }
    return retval;
}

int test_copy_constructor() { // copy (uncomment map prints)
    int retval = 0;
    std::string METHOD = "test_copy_constructor";
    // Arrange
    hash_map<int, float> a(3, 1, 0.95);
    a.insert(1, 1);
    a.insert(2, 4);
    a.insert(3, 9);
    a.insert(4, 16);
    a.insert(5, 25);

    // Act
    hash_map<int, float> b(a);

    // Assert
    if (a.get_size() == b.get_size()) {
        cout << METHOD << " - Test Passed (Size)" << endl;
    }
    else {
        retval++;
        cout << METHOD << " - Incorrect, the sizes do not match. a: " << a.get_size() << "b: " << b.get_size() << endl;
    }
    if (a.get_capacity() == b.get_capacity()) {
        cout << METHOD << " - Test Passed (Capacity)" << endl;
    }
    else {
        retval++;
        cout << METHOD << " - Incorrect, the capacities do not match. a: " << a.get_capacity() << "b: " << b.get_capacity() << endl;
    }
    //a.print_map();
    //b.print_map();
    return retval;
}

int test_assignment() { // assignment (uncomment map prints)
    int retval = 0;
    std::string METHOD = "test_assignment";
    // Arrange
    hash_map<int, float> a(3, 1, 0.95);
    a.insert(1, 1);
    a.insert(2, 4);
    a.insert(3, 9);
    a.insert(4, 16);
    a.insert(5, 25);

    // Act
    hash_map<int, float> b = a;

    // Assert
    if (a.get_size() == b.get_size()) {
        cout << METHOD << " - Test Passed (Size)" << endl;
    }
    else {
        retval++;
        cout << METHOD << " - Incorrect, the sizes do not match. a: " << a.get_size() << "b: " << b.get_size() << endl;
    }
    if (a.get_capacity() == b.get_capacity()) {
        cout << METHOD << " - Test Passed (Capacity)" << endl;
    }
    else {
        retval++;
        cout << METHOD << " - Incorrect, the capacities do not match. a: " << a.get_capacity() << "b: " << b.get_capacity() << endl;
    }
    //a.print_map();
    //b.print_map();
    return retval;
}
int test_self_assignment() {
    int retval = 0;
    std::string METHOD = "test_self_assignment";
    // Arrange
    hash_map<int, float> a(3, 1, 0.95);
    a.insert(1, 1);
    a.insert(2, 4);
    a.insert(3, 9);
    a.insert(4, 16);
    a.insert(5, 25);

    // Act
    a = a;

    // Assert
    if (a.get_size() == 5) {
        cout << METHOD << " - Test Passed (Size)" << endl;
    }
    else {
        retval++;
        cout << METHOD << " - Incorrect, the size is not the same. a: " << a.get_size() << endl;
    }
    if (a.get_capacity() == 209) {
        cout << METHOD << " - Test Passed (Capacity)" << endl;
    }
    else {
        retval++;
        cout << METHOD << " - Incorrect, the capacity is not the same. a: " << a.get_capacity() << endl;
    }
    //a.print_map();
    return retval;
}

int test_bucket_size_three() { // get_bucket_sizes
    int retval = 0;
    std::string METHOD = "test_bucket_size_three";
    // Arrange
    hash_map<int, float> map(3, 1, 0.95);

    // Act
    map.insert(1, 1);
    map.insert(2, 4);
    map.insert(3, 9);
    map.insert(4, 16);
    map.insert(5, 25);

    // Assert
    //map.print_map();
    size_t buckets [map.get_capacity()];
    map.get_bucket_sizes(buckets);
    if (map.get_size() == 5) {
        cout << METHOD << " - Test Passed (Size)" << endl;
    }
    else {
        retval++;
        cout << METHOD << " - Incorrect _size, should be 5 but is " << map.get_size() << endl;
    }
    if (buckets[0] == 0) {
        cout << METHOD << " - Test Passed (Bucket size index 0)" << endl;
    }
    else {
        retval++;
        cout << METHOD << " - Incorrect bucket size for index 0, should be 0 but is " << buckets[0] << endl;
    }
    if (buckets[1] == 1) {
        cout << METHOD << " - Test Passed (Bucket size index 1)" << endl;
    }
    else {
        retval++;
        cout << METHOD << " - Incorrect bucket size for index 1, should be 1 but is " << buckets[1] << endl;
    }
    if (buckets[2] == 1) {
        cout << METHOD << " - Test Passed (Bucket size index 2)" << endl;
    }
    else {
        retval++;
        cout << METHOD << " - Incorrect bucket size for index 2, should be 1 but is " << buckets[2] << endl;
    }
    return retval;
}


int test_get_keys_three() { // get_all_keys
    int retval = 0;
    std::string METHOD = "test_get_keys_three";
    // Arrange
    hash_map<int, float> map(3, 1, 0.95);

    // Act
    map.insert(1, 1);
    map.insert(2, 4);
    map.insert(3, 9);
    map.insert(4, 16);
    map.insert(5, 25);

    // Assert
    //map.print_map();
    int keys [map.get_size()];
    map.get_all_keys(keys);
    if (map.get_size() == 5) {
        cout << METHOD << " - Test Passed (Size)" << endl;
    }
    else {
        retval++;
        cout << METHOD << " - Incorrect _size, should be 5 but is " << map.get_size() << endl;
    }
    if (keys[0] == 1) {
        cout << METHOD << " - Test Passed (First key)" << endl;
    }
    else {
        retval++;
        cout << METHOD << " - Incorrect key for index bucket 0, should be 1 but is " << keys[0] << endl;
    }
    if (keys[1] == 2) {
        cout << METHOD << " - Test Passed (Second key)" << endl;
    }
    else {
        retval++;
        cout << METHOD << " - Incorrect key for index bucket 1, should be 2 but is " << keys[1] << endl;
    }
    if (keys[2] == 3) {
        cout << METHOD << " - Test Passed (Third key)" << endl;
    }
    else {
        retval++;
        cout << METHOD << " - Incorrect key for index bucket 1, should be 3 but is " << keys[2] << endl;
    }
    if (keys[3] == 4) {
        cout << METHOD << " - Test Passed (Fourth key)" << endl;
    }
    else {
        retval++;
        cout << METHOD << " - Incorrect key for index bucket 2, should be 4 but is " << keys[3] << endl;
    }
    if (keys[4] == 5) {
        cout << METHOD << " - Test Passed (Fifth key)" << endl;
    }
    else {
        retval++;
        cout << METHOD << " - Incorrect key for index bucket 2, should be 5 but is " << keys[4] << endl;
    }
    return retval;
}

int test_get_sorted_keys() { 
    int retval = 0;
    std::string METHOD = "test_get_sorted_keys";
    // Arrange
    hash_map<int, float> map(3, 1, 0.95);

    // Act
    map.insert(6, 3);
    map.insert(2, 4);
    map.insert(3, 9);
    map.insert(4, 16);
    map.insert(5, 25);

    // Assert
    //map.print_map();
    int keys [map.get_size()];
    map.get_all_sorted_keys(keys);
    if (map.get_size() == 5) {
        cout << METHOD << " - Test Passed (Size)" << endl;
    }
    else {
        retval++;
        cout << METHOD << " - Incorrect _size, should be 5 but is " << map.get_size() << endl;
    }
    if (keys[0] == 2) {
        cout << METHOD << " - Test Passed (First key)" << endl;
    }
    else {
        retval++;
        cout << METHOD << " - Incorrect key for index bucket 0, should be 1 but is " << keys[0] << endl;
    }
    if (keys[1] == 3) {
        cout << METHOD << " - Test Passed (Second key)" << endl;
    }
    else {
        retval++;
        cout << METHOD << " - Incorrect key for index bucket 1, should be 2 but is " << keys[1] << endl;
    }
    if (keys[2] == 4) {
        cout << METHOD << " - Test Passed (Third key)" << endl;
    }
    else {
        retval++;
        cout << METHOD << " - Incorrect key for index bucket 1, should be 3 but is " << keys[2] << endl;
    }
    if (keys[3] == 5) {
        cout << METHOD << " - Test Passed (Fourth key)" << endl;
    }
    else {
        retval++;
        cout << METHOD << " - Incorrect key for index bucket 2, should be 6 but is " << keys[3] << endl;
    }
    if (keys[4] == 6) {
        cout << METHOD << " - Test Passed (Fifth key)" << endl;
    }
    else {
        retval++;
        cout << METHOD << " - Incorrect key for index bucket 2, should be 5 but is " << keys[4] << endl;
    }
    return retval;
}   

void test_increase_bucket(){
    hash_map<int, float> map(100, 1, 1);

    for(int i = 0; i < 1020; i++){
        map.insert(i, i);
    }
    // cout<<map.get_capacity()<<endl;

    // map.get_all_sorted_keys(keys_1);
    // for(int i = 0 ; i < 5; i++) {
    //     std::cout<<keys_1[i];
    // }
}
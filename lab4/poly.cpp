#include <vector>
#include <utility>
#include <cstddef>
#include "poly.h"
#include <iostream>
#include <thread>
#include <algorithm>
#include <iterator>

using power = size_t;
using coeff = int;

/**
 * 
 * @brief Construct a new polynomial object that is the number 0 (ie. 0x^0)
 *
*/
polynomial::polynomial(){
    max_degree = 0;
    // std::vector<std::pair<power, coeff>> poly_input = {{0,0}};
    // polynomial test(poly_input.begin(), poly_input.end());
    // this->hash = test.hash;
    // std::unordered_map<size_t,int> hash;
    this->hash[0] = 0;
}

/**
 * @brief Construct a new polynomial object from an existing polynomial object
 *
 * @param other
 *  The polynomial to copy
 */
polynomial::polynomial(const polynomial &other){
    hash = other.hash;
    max_degree = other.max_degree;
}

/**
 * @brief Prints the polynomial.
 *
 * Only used for debugging, isn't graded.
 *
 */

void polynomial::print()
{
    auto temp = this->canonical_form();
    //std::sort(polyterms.begin(), polyterms.end(), [](auto &left, auto &right) {return left.second < right.second;});
    for(auto it = (temp.begin()); it != temp.end(); it++) //iterate through other's terms
    {
        std::cout << it->second << "x^" << it->first << std::endl;
        /*if(it != prev(polyterms.rend())) 
        {
            std::cout << " + ";
        }*/
        
    }
    std::cout << "\n";
}

/**
 * @brief Turn the current polynomial instance into a deep copy of another
 * polynomial
 *
 * @param other
 * The polynomial to copy
 * @return
 * A reference to the copied polynomial
 */
polynomial &polynomial::operator=(const polynomial &other){
    if(this == &other){
        return *this;
    }
    hash = other.hash;
    max_degree = other.max_degree;
    return *this;
}

/**
 * Overload the +, * and % operators. The function prototypes are not
 * provided.
 * 
 * Addition (+) should support
 * 1. polynomial + polynomial
 * 2. polynomial + int
 * 3. int + polynomial
 * 
 * Multiplication (*) should support
 * 1. polynomial * polynomial
 * 2. polynomial * int
 * 3. int * polynomial
 * 
 * Modulo (%) should support
 * 1. polynomial % polynomial
 */

polynomial polynomial::operator+(const polynomial &other) const{
    polynomial retVal;
    
    for(auto list1Begin = this->hash.begin(); list1Begin != this->hash.end(); list1Begin++){
        if(list1Begin->second != 0){
            retVal.hash[list1Begin->first] = list1Begin->second;
        }
        // list1Begin++;
    } 
    for(auto list2Begin = other.hash.begin(); list2Begin != other.hash.end(); list2Begin++){
        if(list2Begin->second != 0){
            if(retVal.hash.count(list2Begin->first)){
                retVal.hash[list2Begin->first] = retVal.hash[list2Begin->first] + list2Begin->second;
            } else {
                retVal.hash[list2Begin->first] = list2Begin->second;
            }
        }
        // list2Begin++;
    }     
    retVal.max_degree = retVal.find_degree_of();   
    return retVal;
}


void threadMultiple(const polynomial &firstPoly, const polynomial &secondPoly, polynomial &retVal) { 
    // auto iterEnd = firstPoly.hash.begin();
    // advance(iterEnd, end);
    // auto iterStart = firstPoly.hash.begin();
    // advance(iterStart, start);
    for(auto iterStart = firstPoly.hash.begin(); iterStart != firstPoly.hash.end(); iterStart++){
        for(auto iter2 = secondPoly.hash.begin(); iter2 != secondPoly.hash.end(); iter2++){
            int tempCoeff = iterStart->second * iter2->second;
            int tempPower = iterStart->first + iter2->first;
            if(tempCoeff != 0){
                // if(retVal.hash.count(tempPower)){
                retVal.hash[tempPower] += tempCoeff;
                // } else {
                //     retVal.hash[tempPower] = tempCoeff;
                // }
            }
        }
    }
}

polynomial polynomial::operator*( const polynomial &other) const{  
    int MAX_THREADS = 8;
    if(other.hash.size() > this->hash.size()){
        return other * *this;
    }
    int biggest = this->hash.size();
    // return other;
    polynomial retVal2[MAX_THREADS];  
    std::vector<polynomial> polyStorage(8);
    std::vector<std::thread> threads; 

    // int load = biggest / MAX_THREADS;

    //help from friend and TA
    int bucket_num = 0;
    for(auto iter = this->hash.begin(); iter != this->hash.end(); iter++){        
        polyStorage[bucket_num % 8].hash[iter->first] = iter->second;
        bucket_num += 1; 
    }

    for(int i = 0; i < MAX_THREADS; i++){
        // int start = i * load;
        // int end = (i + 1) * load;

        // if(i == (MAX_THREADS - 1)){
        //     end = biggest;
        // }
        threads.push_back(std::thread(threadMultiple, std::cref(polyStorage[i]), std::cref(other), std::ref(retVal2[i])));
    }

    for(auto& thread : threads){
        thread.join();
    }
    polynomial retVal3 = retVal2[0];
    for(int j = 1; j < MAX_THREADS; j++){
        retVal3 = retVal3 + retVal2[j];
    }
    retVal3.max_degree = retVal3.find_degree_of();
    return retVal3;
}

polynomial polynomial::operator*(const int other) {
    if(other == 0){
        polynomial retVal;
        retVal.hash[0] = 0;
        retVal.max_degree = 0;
        return retVal;
    }
    polynomial retVal;
    // retVal.hash[0] = 0;
    retVal.max_degree = 0;
    for(auto iter = this->hash.begin(); iter != this->hash.end(); iter++){        
        retVal.hash[iter->first] = other * iter->second;
    }
    // retVal.hash.erase(0);
    retVal.max_degree = retVal.find_degree_of();
    return retVal;
}

polynomial operator*(int other, const polynomial& poly){
    if(other == 0){
        // printf("hi");
        polynomial retVal;
        retVal.hash[0] = 0;
        retVal.max_degree = 0;
        return retVal;
    }
    polynomial retVal;
    // retVal.hash[0] = 0;
    // printf("index 0 %d\n", retVal.hash[0]);
    retVal.max_degree = 0;
    for(auto iter = poly.hash.begin(); iter != poly.hash.end(); iter++){        
        retVal.hash[iter->first] = other * iter->second;
    }
    // printf("hi");
    // retVal.hash.erase(0);
    retVal.max_degree = retVal.find_degree_of();
    return retVal;
}



// Overloaded operator+ for adding a polynomial to an integer
polynomial polynomial::operator+(const int other) {
    polynomial retVal = *this;
    if(retVal.hash.count(0)){
        retVal.hash[0] = retVal.hash[0] + other;
    } else {
        retVal.hash[0] = other;
    }
    return retVal;
}

polynomial operator+(int other, const polynomial& poly) {
    polynomial retVal = poly;
    // if(retVal.hash.count(0)){
    //     printf("hi");
    retVal.hash[0] = retVal.hash[0] + other;
    // } else {
    //     retVal.hash[0] = other;
    // }
    return retVal;
}

polynomial polynomial::operator%(const polynomial &inputOther) const{
    return inputOther;
    if(inputOther.max_degree > this->max_degree){
        return *this;
    }
    polynomial temp_dividend = *this; // this
    polynomial other(inputOther);
    // int hello = 0;
    while(other.max_degree <= temp_dividend.max_degree){ // other is divisor
        // printf("jello");
        size_t diff = temp_dividend.max_degree - other.max_degree;
        std::vector<std::pair<power, coeff>> poly_input = {{diff, 1}};
        // polynomial p1 = poly_input * other;
        polynomial p1(poly_input.begin(), poly_input.end());
        p1 = p1 * other;
        p1 = p1 * -1;
        temp_dividend = temp_dividend + p1;
        temp_dividend = polynomial(temp_dividend.hash.begin(), temp_dividend.hash.end());
        temp_dividend.max_degree = temp_dividend.find_degree_of();
        // if(temp_dividend.hash[temp_dividend.max_degree] < other.hash[temp_dividend.max_degree]){
        //     return temp_dividend;
        // }
        // printf("Canonical form: ");
        // for (auto i = temp_dividend.hash.begin(); i != temp_dividend.hash.end(); i++)
        // {
        //     printf("(%d,%d) ", i->first, i->second);
        // }
        // std::cout << temp_dividend.max_degree << std::endl;
        // if(hello == 2){
        //     break;
        // }
        // hello++;
    }
    return temp_dividend;
}

/**
 * @brief Returns the degree of the polynomial
 *
 * @return size_t
 *  The degree of the polynomial
 */

size_t polynomial::find_degree_of(){
    std::unordered_map<size_t,int>::iterator hash_iter = this->hash.begin();
    std::unordered_map<size_t,int>::iterator hash_iter_end = this->hash.end();
    int temp_max_degree = 0;
    while(hash_iter != hash_iter_end){
        if(int(hash_iter->first) > temp_max_degree){
            temp_max_degree = hash_iter->first;
        }
        hash_iter++;
    }
    return temp_max_degree;
}

/**
 * @brief Returns a vector that contains the polynomial is canonical form. This
 *        means that the power at index 0 is the largest power in the polynomial,
 *        the power at index 1 is the second largest power, etc.
 *
 *        ie. 7x^4 + x^2 + 1 would be returned as [(4,7),(2,1),(0,1)]
 *
 *        Note: any terms that have a coefficient of zero aren't returned in
 *        in the canonical form, with one exception.
 *        See the above example (there's no x^3 term, so
 *        there's no entry in the vector for x^3)
 *
 *        The only exception to this is the polynomial 0. If your polynomial is
 *        just the constant 0 then you would return a single entry of [(0,0)]
 *
 *        ie. y = 0 would be returned as [(0,0)]
 *
 * @return std::vector<std::pair<power, coeff>>
 *  A vector of pairs representing the canonical form of the polynomial
 */

std::vector<std::pair<power, coeff>> polynomial::canonical_form() const{
    std::vector<std::pair<power, coeff>> retVal;
    if(this->hash.size() == 1){
        retVal.push_back({this->hash.begin()->first, this->hash.begin()->second});

    }
    else{
        for(auto iter = this->hash.begin(); iter != this->hash.end(); iter++){
            if(iter->second != 0){
                retVal.push_back({iter->first, iter->second});
            }
        }
    }

    std::sort(retVal.begin(), retVal.end());
    std::reverse(retVal.begin(), retVal.end());
    return retVal;
}
#include <iostream>
#include "poly.h"
#include <vector>
#include <map>
#include <thread>
#include <algorithm>

/*Grading for Part 2: - 30 secs or less for sparse 
                      - mod 5 seconds or less 
*/

/*polynomial::polynomial(const polynomial &other)
{
    polyterms.clear(); //ensure map is clear before copying over
    for(const auto &pterm : other.polyterms) //iterate through other's terms
    {
        power pow = pterm.first;
        coeff coe = pterm.second;
        polyterms[pow] = coe;  
    }
}*/

void polynomial::print() const
{
    //std::sort(polyterms.begin(), polyterms.end(), [](auto &left, auto &right) {return left.second < right.second;});
    for(auto it = (polyterms.begin()); it != polyterms.end(); it++) //iterate through other's terms
    {
        std::cout << it->second << "x^" << it->first;
        /*if(it != prev(polyterms.rend())) 
        {
            std::cout << " + ";
        }*/
        
    }
    std::cout << "\n";
}

void polynomial::filter_out_zeros()
{
    std::unordered_map<power,coeff> new_map; 
    for(const auto &pterm : polyterms)
    {
        if(pterm.second != 0)
        {
            new_map[pterm.first] = pterm.second;
        }
    }
    polyterms = std::move(new_map); 
}

/*polynomial &polynomial::operator=(const polynomial &other)
{
    if(this == &other) return *this; //if they're already equal
    polynomial temp = other; 
    std::swap(this->polyterms, temp.polyterms); 
    return *this; 
}*/
/*polynomial polynomial::operator-(const polynomial &other) const
{
    polynomial sub_res; 

    for(const auto &pterm : polyterms)
    {
        sub_res.polyterms[pterm.first] += pterm.second;
    }

    for(const auto &pterm : other.polyterms)
    {
        sub_res.polyterms[pterm.first] -= pterm.second;
    }
    sub_res.filter_out_zeros();
    return sub_res; 
}*/

polynomial polynomial::operator+(const polynomial &other) const
{
    polynomial add_res; 

    for(const auto &pterm : polyterms)
    {
        add_res.polyterms[pterm.first] += pterm.second;
    }

    for(const auto &pterm : other.polyterms)
    {
        add_res.polyterms[pterm.first] += pterm.second;
    }
    add_res.filter_out_zeros();
    return add_res; 
}

polynomial polynomial::operator+(int other) const
{
    polynomial add_res(*this);  
    add_res.polyterms[0] += other; 
    add_res.filter_out_zeros();
    return add_res; 
}

polynomial operator+(int otheri, const polynomial &otherp) 
{
    return (otherp + otheri); 
}

void mult_helper(const polynomial &poly1, const polynomial &poly2, polynomial &mul_res) 
{

    for(const auto &pterm : poly1.polyterms) 
    {
        for(const auto &ptermi : poly2.polyterms) 
        {
            power pow = pterm.first + ptermi.first; 
            coeff coe = pterm.second * ptermi.second; 
            mul_res.polyterms[pow] += coe; 
        }
    }
}

polynomial polynomial::operator*(const polynomial &other) const
{

    if(polyterms.size() < other.polyterms.size())
    {
        return other * *this; 
    }

    size_t bucket_num = 8; //8 buckets, rec from Raghav

    std::vector<polynomial> results(bucket_num);

    std::vector<std::thread> mul_threads;

    std::vector<polynomial> buckets(bucket_num);

    size_t t = 0;
    for(const auto &pterm : polyterms)
    {
        power pow = pterm.first;
        coeff coe = pterm.second;
        buckets[t % bucket_num].polyterms[pow] = coe;
        t += 1; 
    }

    for(int i = 0; i < bucket_num; i++)
    {
        std::thread T(mult_helper, std::cref(buckets[i]), std::cref(other), std::ref(results[i]));
        mul_threads.push_back(std::move(T)); //might need to use std::move instead'
    }

    for(int i = 0; i < bucket_num; i++)
    {
        mul_threads[i].join(); //join the threads
    }

    polynomial sum; 

    for(size_t i = 0; i < bucket_num; i++)
    {
        sum = sum + results[i]; 
    }
    sum.filter_out_zeros();
    return sum; 

}

polynomial polynomial::operator*(int other) const
{
    polynomial mul_res; 

    for(const auto &pterm : polyterms)
    {
        mul_res.polyterms[pterm.first] = pterm.second * other; 
    }
    mul_res.filter_out_zeros();
    return mul_res; 
}

polynomial operator*(int otheri, const polynomial &otherp) 
{
    return (otherp * otheri); 
}

polynomial polynomial::operator%(const polynomial &other) const
{
    polynomial d(other); //make copy of other for find_degree_of
    polynomial r(*this); //make deep copy of this
    power tempow;
    coeff tempcoeff;
    while((r.find_degree_of() >= d.find_degree_of())) 
    {
        tempcoeff = r.polyterms[r.find_degree_of()] / d.polyterms[d.find_degree_of()];
        tempow = r.find_degree_of() - d.find_degree_of();
        polynomial temp;
        temp.polyterms[tempow] = tempcoeff;
        r = r + (temp * -1) * d; 
    }
    r.filter_out_zeros();
    return r; 
}

size_t polynomial::find_degree_of()
{  
    size_t degree = 0; 
    size_t temp = 0;
    for(const auto &pterm : polyterms)
    {
        temp = pterm.first; 
        if(temp > degree)
        {
            degree = temp; 
        }
    }
    return degree; 
}

std::vector<std::pair<power, coeff>> polynomial::canonical_form() const
{
    std::vector<std::pair<power, coeff>> retval; 
    std::pair<power,coeff> retpair;
    /*for(auto it = polyterms.rbegin(); it != polyterms.rend(); it++) //iterate through other's terms
    {
        retpair.first = it -> first; 
        retpair.second = it -> second; 
        if(it -> second != 0) //remove zeros 
        {
            retval.push_back(retpair);
        }

    }*/
    for(auto it = polyterms.begin(); it != polyterms.end(); it++) //iterate through other's terms
    {
        retpair.first = it -> first; 
        retpair.second = it -> second; 
        if(it -> second != 0) //remove zeros 
        {
            retval.push_back(retpair);
        }

    }
    if(retval.empty()) //if 0 map...
    {
        retval.push_back({0,0});
    }
    std::sort(retval.begin(), retval.end(), [](auto &left, auto &right) {return left.first > right.first;});
    return retval; 
}


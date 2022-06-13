/***************************
** File: hashtable_seperate_chaining.h
** Author: Zia Uddin
** Date: 4/11/2022
** Section: 511
** Email: zia19@tamu.edu
**
** This file contains the class definition for a seperate-addressing hashtable.
** the seperate-addressing hashtable is implemented using std::vector and std::list 
** as well as the standard library hash function. collisions are handled by linked list using push_back()
**
***************************/

#ifndef HASHTABLE_SEPARATE_CHAINING_H
#define HASHTABLE_SEPARATE_CHAINING_H

#include <vector>
#include <list>
#include <stdexcept>
#include <functional>
#include <iostream>

using std::list, std::vector, std::cout, std::cin, std::endl;

template <class Key, class Hash=std::hash<Key>>
class HashTable {
public:
    // Member Types - do not modify
    using key_type = Key;
    using value_type = Key;
    using hash = Hash;
    using size_type = size_t;
    // you can write your code below this

private:
    // TODO: student implementation
    
    size_type _size; // number of existing values in table
    size_type _buckets; // number of linked list in vector
    float MaxLF;
    vector<list<Key>> table;

    // hash function returns hashed index
    size_t hashFunction(const Key& value) const
    {
        Hash hashedValue;
        return hashedValue(value) % _buckets;
    }

    // checks if number is prime and is used in nextPrime function
    size_t isPrime(size_t n)
    {
        size_t i;
        if (n == 1 || n == 0)
            return 0;
        for (i = 2; i < n / 2; i++)
        {
            if(n%i == 0)
                return 0;
        }
        return 1;
    }

    // finds next prime number from given parameter n
    // used in rehash function because we want to make sure table size is prime to maintain performance
    size_t nextPrime(size_t n)
    {
        if (n % 2 == 0)
            n++;

        while (!isPrime(n))
        {
            n += 2;
        }
        return n;
    }


public:
    HashTable() : _size{0}, _buckets{11}, MaxLF{1} {table.resize(11);}

    HashTable(const HashTable& other) : _size{other._size}, _buckets{other._buckets}, MaxLF{other.MaxLF}, table{other.table} {}

    ~HashTable()
    {
        if (!is_empty())
            make_empty();
    }

    HashTable& operator=(const HashTable& other)
    {
        if (this == &other) // check for self assignment
        {
            return *this;
        }
        
        _size = other._size;
        _buckets = other._buckets;
        table = other.table;
        MaxLF = other.MaxLF;

        return *this;
    }

    HashTable(size_type buckets) : _size{0}, _buckets{buckets}, MaxLF{1} {table.resize(buckets);} 
    
    bool is_empty() const
    {
        return _size == 0;
    }

    size_t size() const
    {
        return _size;
    }

    void make_empty()
    {
        // for each linked list in table, clear its contents and reset size
        for(auto& table : table)
            table.clear();
        _size = 0;

    }


    bool insert(const value_type& value)
    {
        auto& bucket = table.at(hashFunction(value)); // find which linked list to insert into

        // find function will return value if exists in linked list otherwise returns last value
        auto valueExist = find(bucket.begin(), bucket.end(), value); 
        if (valueExist != bucket.end()) // if find doesnt return last value exit function and return false
            return false;

        bucket.push_back(value);
        ++_size;

        if (load_factor() > MaxLF)
        {
            rehash(2*_buckets); // rehash with table roughly doubled in size
        }
        return true;
    }

    size_t remove(const key_type& key)
    {
        auto& bucket = table.at(hashFunction(key));  // find which linked list to insert into

        // find function will return value if exists in linked list otherwise returns last value
        auto value = find(bucket.begin(), bucket.end(), key); 

        if (value != bucket.end()) // if find function returns value passed in
        {
            bucket.erase(value);
            --_size;
            return true;
        }
        return false; // if find funciton returns last value in list
    }

    bool contains(const key_type& key)
    {
        auto& bucket = table.at(hashFunction(key));
        return find(begin(bucket), end(bucket), key) != end(bucket);
    }
    
    size_t bucket_count() const
    {
        return _buckets;
    }
    size_t bucket_size(size_t n) const
    {
        return table.at(n).size();
    }

    size_t bucket(const key_type& key) const
    {
        return hashFunction(key);
    }

    float load_factor() const
    {
        return static_cast<float>(_size) / static_cast<float>(_buckets);
    }
    
    float max_load_factor() const
    {
        return MaxLF;
    }
    void max_load_factor(float mlf)
    {
        if (mlf <= 0)
            throw std::invalid_argument("invalid load factor value");
        
        if (mlf < load_factor())
            rehash(2*_buckets);
        MaxLF = mlf;
    }

    
    void rehash(size_type count)
    {
        vector<list<Key>> originalTable = table; // copy of original hash table

        table.resize(nextPrime(count));   // erases each linked list or "bucket" in hash table
        for (auto& tableBucket: table)
            tableBucket.clear();

        _size = 0;
        _buckets = nextPrime(count); 
        // rehashes and inserts existing elements into newly sized hash table
        for(auto& tableBucket : originalTable)  // for each bucket in the copy of original hash table
            for(auto& value: tableBucket) // for each value in bucket of orginal hash table
                insert(value);
    }
    
    void print_table(std::ostream& os=std::cout) const
    {
        if (is_empty())
        {
            cout << "<empty" << endl;
            return;
        }
        size_t cntr = 0;
        for (auto& bucket: table)
        {
            os << cntr << "|-------------------------------------------------------" << endl;
            cntr++;
            for (auto& value: bucket)
                os << "      " <<value << " ";
            os << endl;
        }
        os << "  " << "|-------------------------------------------------------" << endl;
        os << endl;
    }

  
    // Optional
    // HashTable(HashTable&& other);
    // HashTable& operator=(HashTable&& other);
    // bool insert(value_type&& value);
};

#endif  // HASHTABLE_SEPARATE_CHAINING_H

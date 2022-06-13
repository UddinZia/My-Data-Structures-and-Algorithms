/***************************
** File: hashtable_open_addressing.h
** Author: Zia Uddin
** Date: 4/11/2022
** Section: 511
** Email: zia19@tamu.edu
**
** This file contains the class definition for an open-addressing hashtable.
** the open-addressing hashtable is implemented using a vector and standard 
** library hash function. the collision funciton is quadratic. 
**
***************************/

#ifndef HASHTABLE_OPEN_ADDRESSING_H
#define HASHTABLE_OPEN_ADDRESSING_H

#include <functional>
#include <iostream>
#include <vector>

using std::vector, std::cout, std::endl;

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

    // hash function returns hashed index
    size_t hashFunction(const Key& value) const
    {
        Hash hashedValue;
        return hashedValue(value) % this->table_size();
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

    /*
     enum used for determining if a cell has a live value, is empty, or has a value that was deleted
    cannot delete value directly because it will cause other operations to fail. enum used in EntryType struct
    */
    enum EntryType{ACTIVE, EMPTY, DELETED};

    /*
    hashEntry is passed into table as its data type. contains the actual value and the enum EntryType information 
    */
    struct hashEntry
    {
        Key value;
        EntryType info;

        hashEntry( const Key & e = Key{ }, EntryType i = EMPTY ) 
         : value{ e }, info{ i } {}
    };

    vector<hashEntry> table; // creates a vector of hashEntry objects that contain a value and EntryType info
    size_type _size; // number of existing values in table
    float MaxLF;

    //returns if cell has a live value that was not deleted or empty
    bool IsActive(size_t pos) const 
    {
        return table.at(pos).info == ACTIVE;
    }


    /*
    * rehash called when load factor exceeds maximum load factor
    * created copy of table and resizes table to roughly 2x its 
    * original size using nextPrime function.
    */
    void rehash()
    {
        vector<hashEntry> copyArr = table;

        // resize table and make cells empty
        table.resize(nextPrime(2 * copyArr.size()));
        for (auto& cell: table)
            cell.info = EMPTY;

        //copy values from copyArr to table
        _size = 0;
        for (auto& cell: copyArr)
            if (cell.info == ACTIVE)
                insert(cell.value);
    }
    

public:
    HashTable() : _size{0}, MaxLF{0.5} {table.resize(11);} 
    HashTable(const HashTable& other) : table{other.table}, _size{other._size}, MaxLF{other.MaxLF} {}
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
        table = other.table;
        MaxLF = other.MaxLF;

        return *this; 
    }

    HashTable(size_type cells) : _size{0}, MaxLF{0.5} {table.resize(cells);}

    bool is_empty() const
    {
        return _size == 0;
    }

    size_t size() const
    {
       return _size;
    }

    size_t table_size() const
    {
        return table.size();
    }

    void make_empty()
    {
        _size = 0;
        for (auto& cell : table) // cannot delete elements directly so set enum value to EMPTYY
            cell.info = EMPTY;
    }

    /*
    * insert funciton depends on position function which returns correct position to insert to. 
    * sets object value to value passed in and status to active
    */
    bool insert(const value_type& value)
    {
       size_t currentCell = position(value); // finds correct position to insert into using position function
       if (IsActive(currentCell)) // if value exists exit function and return false
        return false;

        // assign value & info to hashEntry object at currentPos 
       table.at(currentCell).value = value; 
       table.at(currentCell).info = ACTIVE;
       ++_size;

       if (load_factor() > MaxLF) 
       {
           rehash();
       }
       return true;
        
    }

    
    /*
    * remove funciton depends on position function which returns correct position to delete from. 
    * sets object value to value passed in and status to active
    */
    size_t remove(const key_type& key)
    {
        size_t currentPos = position(key);  // finds correct position to remove using position function
        if (!IsActive(currentPos)) // if value doesn't exists, exit function and return false
            return false;

        table.at(currentPos).info = DELETED; // if found set status of object to deleted and decrease # of elements in table
        --_size;
        return true;
    }

    bool contains(const key_type& key)
    {
       return IsActive(position(key));
    }

    /*
    * collision resolution function that returns correct position to insert/delete into.
    * is used in insert,remove, and contains
    */
    size_t position(const key_type& key) const
    {

        size_t offset = 1;
        size_t currentPos = hashFunction(key);

        // if current cell is not empty and does not contain value passed in
        while (table.at(currentPos).info != EMPTY && table.at(currentPos).value != key)
        {
            currentPos += offset;
            offset += 2;
            // substract currentPos from table size to get correct position 
            if (currentPos >= table.size())
                currentPos -= table.size();
        }
        return currentPos;
    }

    void print_table(std::ostream& os=std::cout) const
    {
        if (is_empty())
        {
            cout << "<empty>" << endl;
            return;
        }

        size_t cntr = 0;
        for (auto& cell : table)
        {
            cout << "table[" << cntr << "]" << "-----> " << cell.value << endl; 
            cntr++;
        }
    }

    float load_factor() const
    {
        return static_cast<float>(_size) / static_cast<float>(table_size());
    }

    // Optional
    // HashTable(HashTable&& other);
    // HashTable& operator=(HashTable&& other);
    // bool insert(value_type&& value);
};

#endif  // HASHTABLE_OPEN_ADDRESSING_H

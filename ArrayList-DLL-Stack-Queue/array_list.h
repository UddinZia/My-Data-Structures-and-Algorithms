#ifndef ARRAY_LIST_H
#define ARRAY_LIST_H

#include <cstddef>
#include <stdexcept>

#include <iostream>
using std:: cout, std::cin, std::endl;

template <typename Object>
class ArrayList {
private:
    Object* thing;
    size_t _size;
    size_t Capacity;


public:
    ArrayList() : thing{new Object[1]}, _size{0}, Capacity{1} {} // default constructor
    
    ArrayList(size_t _capacity) : thing{new Object[_capacity]}, _size{0}, Capacity{_capacity} {}      // parameterized constructor

    ArrayList(const ArrayList& other) : thing{nullptr}, _size{other.size()}, Capacity{other.Capacity}     // copy constructor
    {
        thing = new Object[Capacity];
        for (size_t i = 0; i < _size; i++)
        {
            thing[i] = other.thing[i];
        }
    } 

    ~ArrayList() {delete [] thing;}
    
    ArrayList& operator=(const ArrayList& other)  // copy assignment 
    {
        
        if (this == &other) // check for self assignment
        {
            return *this;
        }

        delete [] thing;
        _size = other.size();
        Capacity = other.Capacity;
        thing = new Object[Capacity];
        for (size_t i = 0; i < Capacity; i++)
        {
            thing[i] = other.thing[i];
        }

        return *this;
    }

    size_t size() const
    {
        return _size;
    }

    size_t capacity() const
    {
        return Capacity;
    }

    Object& operator[](size_t index)
    {
        if (index >= _size)
        {
            throw std::out_of_range("invalid index bro");
        }
        return thing[index];
    }


    void insert(size_t index, const Object& obj)
    {
    
        if (index > _size)
        {
            throw std::out_of_range("invalid index bro");
        }

        if (_size == Capacity) // if array needs to be resized
        {
            Object* copyArr = new Object[Capacity + 1];
            for (size_t i = 0; i < _size; i++)
            {
                copyArr[i] = thing[i];
            }
            delete [] thing;
            Capacity++;
            thing = copyArr;
        }

        for (size_t i = _size; i > index; --i)
        {
            thing[i] = thing[i-1];
        }
        thing[index] = obj;
        _size++;
    }

    void remove(size_t index)
    {
        if (index >= _size)
        {
            throw std::out_of_range("invalid index bro");
        }

        if (thing == nullptr || _size == 0)
        {
            throw std::invalid_argument("list is empty");
        }

        Object obj = thing[index];

        Object* copyArr = new Object[Capacity];
        size_t j = 0;
        bool isRemoved = false;
        for (size_t i = 0; i < _size; i++)
        {
            if (thing[i] != obj || isRemoved == true) //copies values over if it is not the object to be removed or 1st instance has already been removed
            {
                copyArr[j] = thing[i];
                j++;
            }
            else
            {
                isRemoved = true;
            } 
        }
        delete [] thing;
        thing = copyArr; // calls destructor
        _size--;
        Capacity--;

    }
    void displayList()
    {
        for (size_t i = 0; i < _size; i++)
        {
            cout << thing[i] << " ";
        }
        cout << endl;
    }

};

#endif  

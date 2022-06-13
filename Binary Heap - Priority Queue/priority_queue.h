#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include <iostream>
#include <vector>
#include <functional>
#include "heap.h"

/***************************
** File: priority_queue.h
** Author: Zia Uddin
** Date: 4/22/2022
** This file relies on heap.h to build a priority queue. 
**
******************************/


template <class Comparable, class Container=std::vector<Comparable>, class Compare=std::less<Comparable>>
class PriorityQueue {
private:
    // Member Types - do not modify
    using container_type = Container;
    using value_compare = Compare;
    using value_type = typename Container::value_type;
    using size_type = typename Container::size_type;
    using reference = typename Container::reference;
    using const_reference = typename Container::const_reference;

    Compare compare;
    Container container;
    size_t _size; // keep track of elements 

public:
    PriorityQueue() : _size{0} {}

    PriorityQueue(const PriorityQueue& other) : compare{other.compare}, container{other.container}, _size{other._size} {} // copy

    PriorityQueue(const Compare& _compare) : compare{_compare},  _size{0} {} // comparator 

    PriorityQueue(const Container& _container) : container{_container} // container 
    {
        heapify(&container);
        _size = container.size()-2;
    }

    PriorityQueue(const Compare& _compare, const Container& _container) : compare{_compare}, container{_container} // comparator & container
    {
        heapify(&container,compare);
        _size = container.size()-2;
    }

    ~PriorityQueue() {}

    PriorityQueue& operator=(const PriorityQueue& other)
    {
        compare = other.compare;
        container = other.container;
        _size = other._size;

        return *this;
    }

    const_reference top() const
    {
        if (empty())
            throw std::invalid_argument("queue is empty");

        return heap_get_min(container);
    }

    bool empty() const
    {
        return _size == 0;
    }

    size_type size() const
    {
        return _size;
    }

    void make_empty()
    {
        _size = 0;
        return container.clear();
    }

    void push(const value_type& value)
    {
        heap_insert(&container, value, compare);
        _size++;
    }

    void pop()
    {
        heap_delete_min(&container, compare);
        _size--;
    }

    void print_queue(std::ostream& os=std::cout) const
    {
        if (empty())
            os << "<empty>\n";
        
        for (size_t i = 0; i < size(); i++)
            os << container.at(i) << " ";
        os << std::endl;
    }
};

#endif  // PRIORITY_QUEUE_H

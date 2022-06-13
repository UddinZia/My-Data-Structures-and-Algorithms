#ifndef HEAP_H
#define HEAP_H

#include <functional>

/***************************
** File: heap.h
** Author: Zia Uddin
** Date: 4/22/2022
** This file contains the function defintions for percolate down and heapify. heapify depends 
** on percolate down function for building the heap.
**
******************************/



template <class Container, class Compare=std::less<typename Container::value_type>>
void percolate_down(Container* container, size_t index, Compare less=std::less<typename Container::value_type>{}) 
{

    if (index <= 0 || index > container->size()-1) //
        throw std::invalid_argument("invalid index");
    
    size_t child;
    auto tmp = std::move(container->at(index));
    
    for(; index * 2 <= container->size()-1; index = child)
    {
        child = index * 2;
        if (child != container->size()-1 && less(container->at(child + 1),  container->at(child)))
            ++child;
        if (less(container->at(child) , tmp))
            container->at(index) = std::move(container->at(child));
        else
            break;
    }
    container->at(index) = std::move(tmp);
}


/*
* creates heap by looping thro
*/
template <class Container, class Compare=std::less<typename Container::value_type>>
void heapify(Container* container, Compare less=std::less<typename Container::value_type>{}) {
    // TODO(student): implement heapify
   
  if (container->empty())
    return;

    // resize container since we want to shift values to right
  size_t currentSize = container->size();
  container->resize(container->size()+1);

  for (size_t i = currentSize; i > 0; i--)
    container->at(i) = container->at(i - 1);

  for (size_t i = currentSize / 2; i > 0; i--)
    percolate_down(container, i);
  
}

template <class Container, class Compare=std::less<typename Container::value_type>>
void heap_insert(Container* container, const typename Container::value_type& value, Compare less=std::less<typename Container::value_type>{}) {
    if (container->size() <= 1) {
        container->resize(2);
        container->at(1) = std::move(value);
        return;
    }
    size_t index = container->size();
    container->push_back(value);
    size_t parent = index / 2;
    while (parent > 0 && less(value, container->at(parent))) {
        container->at(index) = std::move(container->at(parent));
        index = parent;
        parent = index / 2;
    }
    container->at(index) = std::move(value);
}

template <class Container>
const typename Container::value_type& heap_get_min(const Container& container) {
    if (container.size() <= 1) {
        throw std::invalid_argument(__FUNCTION__);
    }
    return container[1];
}

template <class Container, class Compare=std::less<typename Container::value_type>>
void heap_delete_min(Container* container, Compare less=std::less<typename Container::value_type>{}) {
    if (container->size() <= 1) {
        throw std::invalid_argument(__FUNCTION__);
    }
    if (container->size() == 2) {
        container->pop_back();
        return;
    }
    container->at(1) = std::move(container->back());
    container->pop_back();
    percolate_down(container, 1, less);
    
}

#endif  // HEAP_H

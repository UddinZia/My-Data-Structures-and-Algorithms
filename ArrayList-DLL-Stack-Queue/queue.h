#ifndef QUEUE_H
#define QUEUE_H

#include <cstddef>
#include <stdexcept>
#include "array_list.h"

template <typename Object>
class Queue {
private:
    // TODO(student): implement Queue
    ArrayList<Object> queue; 
public:
    Queue() {}
    Queue(const Queue& other) : queue{other.queue} {}
    ~Queue() {}
    Queue& operator=(const Queue& other)
    {
        queue = other.queue;
    }
    void enqueue(const Object& item)
    {
        queue.insert(0, item);
    }
    Object dequeue()
    {
        Object data = queue[queue.size() - 1];
        queue.remove(queue.size() - 1);
        return data;
    }
    Object& front()
    {
        return queue[queue.size() - 1];
    }
    size_t size() const
    {
        return queue.size();
    }
};

#endif  // QUEUE_H

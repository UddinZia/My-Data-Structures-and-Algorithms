#ifndef STACK_H
#define STACK_H

#include <cstddef>
#include <stdexcept>
#include "doubly_linked_list.h"

template <typename Object>
class Stack 
{
private:
	DoublyLinkedList<Object> DLL; 
public:
	Stack() {}
	Stack(const Stack& other) : DLL{other.DLL} {}
	~Stack() {}

	Stack& operator=(const Stack& other)
	{
		DLL = other.DLL;
	}
	void push(const Object& item)
	{
		DLL.insert(DLL.size(), item);
	}
	Object pop()
	{
		Object data = DLL[DLL.size() - 1];
		DLL.remove(DLL.size() - 1);
		return data;
	}
	Object& top()
	{
		return DLL[DLL.size() - 1];
	}
	size_t size() const
	{
		return DLL.size();
	}
};

#endif  // STACK_H

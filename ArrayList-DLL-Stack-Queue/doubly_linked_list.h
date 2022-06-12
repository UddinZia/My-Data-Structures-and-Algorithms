#ifndef DOUBLY_LINKED_LIST_H
#define DOUBLY_LINKED_LIST_H

#include <cstddef>
#include <stdexcept>
#include <iostream>

using std::cout, std::endl;

template <typename Object>
class DoublyLinkedList 
{
private:
    struct node
    {   
        Object data;
        node* next;
        node* prev;
    };

    node* head;
    size_t _size;

public:
    DoublyLinkedList()        // default constructo
    {
        head = nullptr;
        _size = 0;
    }
    DoublyLinkedList(const DoublyLinkedList& other) 
    {
        _size = other._size;
        if (other.head == nullptr) // if list is empty
        {
            head = nullptr;
        }
        else
        {
            head = new node();
            head->data = other.head->data;
            
            node* currentOther = other.head->next;
            node* current = head;
            node* currentPrev;
            while (currentOther != nullptr)
            {
                current->next = new node();
                current->next->data = currentOther->data;
                currentPrev = current;
                current = current->next;
                current->prev = currentPrev;
                currentOther = currentOther->next;
            }
        }
    }

    ~DoublyLinkedList()
    {
        while (head)
        {
            node* temp = head->next;
            delete head;
            head = temp;
        }
    }


    DoublyLinkedList& operator=(const DoublyLinkedList& other)
    {
        
        if (this == &other)
        {
            return *this;
        }

        this->~DoublyLinkedList(); // call destructor to delete linked list

        _size = other._size;
        if (other.head == nullptr) // if list is empty
        {
            head = nullptr;
        }
        else // deep copy of nodes
        {
           
            head = new node();               
            head->data = other.head->data;
            
            node* currentOther = other.head->next;
            node* current = head;
            node* currentPrev;
            while (currentOther != nullptr) 
            {
                current->next = new node(); 
                current->next->data = currentOther->data; 
                currentPrev = current;  
                current = current->next; 
                current->prev = currentPrev; 
                currentOther = currentOther->next;
            }
        }
        return *this;
    } 

    size_t size() const
    {
        return _size;
    }

    Object& operator[](size_t index)
    {
        node* current = head;
        size_t i = 0;
        if (index >= _size || index < 0)
        {
            throw std::out_of_range("invalid index bro");
        }
        while(current && (i != index))
        {
            current = current->next;
            i++;
        }
        return current->data;
    }

    void insert(size_t index, const Object& obj)
    {
        if (index > _size || index < 0)
        {
            throw std::out_of_range("invalid index bro");
        }
        
        node* insertNode = new node();
        insertNode->data = obj;
        if (head == nullptr) // empty list
        {
            insertNode->prev = nullptr;
            insertNode->next = nullptr;
            head = insertNode;
        }
        else if (index == 0) // beginning of list
        {
            insertNode->prev = nullptr;
            insertNode->next = head;
            head->prev = insertNode;
            head = insertNode;
        }
        else if (index == _size) // at end of list
        {
            node* last = head;
            while(last->next)
            {
                last = last->next;
            }
            insertNode->prev = last;
            insertNode->next = nullptr;
            last->next = insertNode;
        }
        else //insertion within list
        {
            node* current = head;
            node* temp;
            size_t i = 0;
            while (i != index)
            {
                current = current->next;
                i++;
            }
            temp = current->prev;
            current->prev = insertNode;
            insertNode->prev = temp;
            insertNode->next = current;
            temp->next = insertNode;
        }
        _size++;
    }

    void remove(size_t index)
    {
        if (index >= _size || index < 0)
        {
            throw std::out_of_range("invalid index bro");
        }
        
        if (head == nullptr) // if trying to delete from empty list
        {
            throw std::invalid_argument("list is empty");
        }

        if (index == 0) // delete from front of list
        {
            node* temp = head->next;
            delete head;
            head = temp;
        }
        else if (index == _size-1) // delete from end of list
        {
            node* last = head;
            node* temp;
            while(last->next)
            {
                last = last->next;
            }
            temp = last->prev;
            temp->next = nullptr;
            delete last;
        }
        else // delete within list
        {
            node* current = head;
            node* before;
            node* after;
            size_t i = 0;
            while (i != index)
            {
                current = current->next;
                i++;
            }
            before = current->prev;
            after = current->next;
            before->next = after;
            after->prev = before;
            delete current;
        }
        _size--;
    }

    void printLinkedList() 
    {
        
        node* current = head;
        while(current)
        {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }

};

#endif  // DOUBLY_LINKED_LIST_H

#include <iostream>
#include "doubly_linked_list.h"


using std::cout, std::endl;


int main() 
{
    // TODO(student): test your code
    DoublyLinkedList<char> t1;
    DoublyLinkedList<char> t2;
    DoublyLinkedList<char> t3;
    cout << t3.size() << endl;
    t1.insert(0, '5');
    t1.insert(0, 'a');
    t1.insert(0, 'c');
    //t1.printLinkedList();
    t1.insert(2, '6');
   // t1.printLinkedList();
    t1.insert(1, '8');
   // t1.printLinkedList();
    t1.insert(2, '4');
    //t1.printLinkedList();
    t1.insert(5, '9');
    //t1.printLinkedList();
    //t1.remove(1);
    //t1.printLinkedList();
    //t1.remove('1');
    t3 = t1;
    
    
    t2.insert(0, 'a');
    t2.insert(0, 'b');
    t2.insert(0, 'c');
    t2.insert(0, 'd');
    t2.insert(0, 'e');
    t2.insert(0, 'f');
    t2.insert(0, 'g');
    t2.insert(0, 'h');
    t2.insert(0, 'i');
    t2.insert(0, 'j');
    t2.insert(0, 'k');
    t2.insert(0, 'l');
    t2.insert(0, 'm');
    t2.insert(0, 'n');
    t2.printLinkedList();
    cout << t2.size() << endl;

    t2 = t1;
    t2.printLinkedList();
    t2 = t2;    

    try //insert invalid
    {
        t2.insert(900000, 69);
    }
    catch(const std::exception& e)
    {
        cout << "invalid insert " << endl;
    }
    


    

    
    return 0;
}
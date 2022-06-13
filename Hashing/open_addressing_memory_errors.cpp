#include <iostream>
#include "hashtable_open_addressing.h"

int main() {
    std::cout << "make a hash table" << std::endl;
    HashTable<int> table;
    std::cout << "put a bunch of values in it" << std::endl;
    for (int n = -1000; n <= 1000; n++) {
        table.insert(n);
    }
    {
        std::cout << "construct a copy" << std::endl;
        HashTable<int> copy = table;
        std::cout << "remove some values from original" << std::endl;
        for (int n = -1000; n <= 1000; n+=2) {
            table.remove(n);
        }
        std::cout << "remove some values from copy" << std::endl;
        for (int n = -999; n <= 1000; n+=2) {
            copy.remove(n);
        }
        std::cout << "copy one to the other" << std::endl;
        table = copy;
        std::cout << "remove some more values from both" << std::endl;
        table.remove(887);
        copy.remove(88);
        std::cout << "do self-assignment" << std::endl;
        copy = copy;
        std::cout << "remove some more values" << std::endl;
        table.remove(667);
        copy.remove(66);
        std::cout << "destruct copy" << std::endl;
    }
    std::cout << "remove some values from original" << std::endl;
    for (int n = -1000; n <= 1000; n+=4) {
        table.remove(n);
    }
    std::cout << "do self-assignment" << std::endl;
    table = table;
    std::cout << "make empty" << std::endl;
    for (int n = -1000; n <= 1000; n++) {
        table.remove(n);
    }
    std::cout << "put some values back in" << std::endl;
    table.insert(1);
    table.insert(2);
    table.insert(3);
    std::cout << "make empty again" << std::endl;
    table.remove(1);
    table.remove(2);
    table.remove(3);
    
    return 0;
}

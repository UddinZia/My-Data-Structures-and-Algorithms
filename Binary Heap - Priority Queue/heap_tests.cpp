#include <iostream>
#include <vector>
#include <deque>
#include <array>

#include "heap.h"
#include <functional>

using std::cout, std::endl;

template <class Comparable>
struct GreaterThan {
    constexpr bool operator()(const Comparable& lhs, const Comparable& rhs) const {
        return rhs > lhs;
    }
};

int main() {
   

    
    // Example test case
    std::vector<int> heap{150,80,40,30,10,70,110,100,20,90,60,50,120,140,130};

    cout << "before heapify: ";
    for (int i : heap) { cout << i << " "; }
    cout << endl;

    heapify(&heap);

    cout << "after heapify: ";
    for (int i : heap) { cout << i << " "; }
    cout << endl;

    for (unsigned j = 0; j < 4; j++) {
        cout << "minimum is " << heap_get_min(heap) << endl;
        
        cout << "delete min" << endl;
        heap_delete_min(&heap);
        
        cout << "heap: ";
        for (int i : heap) { cout << i << " "; }
        cout << endl;
    }

    int values[] = {47,54,57,43,120,3};
    for (unsigned j = 0; j < 6; j++) {
        cout << "insert " << values[j] << endl;
        heap_insert(&heap, values[j]);

        cout << "heap: ";
        for (int i : heap) { cout << i << " "; }
        cout << endl;
    }

     std::vector<int> heap1 {150,80,40,20,90,60,50,120,140,130};
    
    //heapify(&heap1);
    heapify(&heap1, GreaterThan<int>{});

    for (size_t i = 1; i < heap1.size(); i++)
    {
        cout << heap1.at(i) << " "; 
    }
    cout << endl;

    cout << heap_get_min(heap1) << endl;


    return 0;
}

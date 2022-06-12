#include <iostream>
#include "array_list.h"


using std:: cout, std::cin, std::endl;

int main() {
    // TODO(student): test your code
    
    ArrayList<int> Arr1;
   // cout << Arr1.size() << " " << Arr1.capacity() << endl;
    Arr1.insert(0, 69);
    //cout << Arr1.size() << " " << Arr1.capacity() << endl;
    Arr1.insert(0, 9);
    //cout << Arr1.size() << " " << Arr1.capacity() << endl;
    Arr1.insert(0, 6);
    Arr1.insert(0, 5);
    Arr1.insert(0, 7);
    Arr1.insert(0, 4);
    Arr1.displayList();
    //Arr1.insert(6,0);
    Arr1.insert(6, 54);
    Arr1.displayList();
    Arr1.insert(4,0);
    Arr1.displayList();
    Arr1.insert(6,420);
    Arr1.displayList();
    //cout << Arr1[4] << endl;
    Arr1.remove(0);
    Arr1.displayList();
    Arr1.remove(3);
    Arr1.displayList();
    Arr1.remove(6);
    Arr1.displayList();
    cout << Arr1.size() << " " << Arr1.capacity() << endl;
    

   /*
    ArrayList<int> Arr2(11);
    Arr2.insert(3, 2); // 3   
    Arr2.insert(6, 69); // 6
    Arr2.insert(9, 4); // 9
    Arr2.insert(5, 4); // 5
    Arr2.insert(0, 1); // 0
    Arr2.insert(1, 0); // 1
    Arr2.insert(4, 8); // 4
    Arr2.insert(2, 7); // 2
    Arr2.insert(7, 21); // 7
    Arr2.insert(8, 99); // 8
    // 0 1 7 2 8 4 69 21 99 4 
    Arr2.displayList();
    cout << Arr2.size() << " " << Arr2.capacity() << endl;
*/

    //Arr2 = Arr1;
  
    ArrayList<char> Arr4(4);
    Arr4.insert(0, 'a');
    Arr4.insert(0, 'b');
    Arr4.insert(0, 'c');
    Arr4.displayList();
}

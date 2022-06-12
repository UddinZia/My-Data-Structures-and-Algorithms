#include <iostream>
#include "binary_search_tree.h"

using std::cout, std::endl;

int main() {
    // TODO(student): write tests
    /*
    int A[] = {63, 41, 76, 93, 66, 5, 10, 57, 8, 79, 29, 14, 73, 56, 54, 87, 60, 22, 23, 90};

    BinarySearchTree<int> tree;
    for (size_t index = 0; index < 20; index++) 
    {
        //tree
        tree.insert(A[index]);
    }


    //cout << tree.find_max() << " " << tree.find_min() << endl;
    BinarySearchTree<int> tree1(tree);
    tree.make_empty();
    tree.print_tree();


    cout << tree1.contains(5) << endl << endl;
    cout << tree1.contains(0) << endl << endl;
    tree1.print_tree();
    tree1.remove(63);
    tree1.remove(90);
    //tree1.print_tree();
    //cout << tree1.find_min() << endl;
    //tree1.print_tree();
    //cout <<  tree1.contains(63) << endl;

   
    BinarySearchTree<int> tree3;
    tree3.insert(5);
    tree3.insert(4);
    tree3.insert(8);
    tree3.insert(8);

    tree3.print_tree();
    */

   BinarySearchTree<int> test;
   test.insert(4);
   test.insert(2);
   test.insert(6);
   test.insert(1);
   test.insert(3);
   test.insert(5);

   //test.print_tree();

   test.remove(6);

   test.print_tree();
}

#include <iostream>
#include "avl_tree.h"

using std::cout, std::endl;

int main() {
    
    
    AVLTree<int> tree;
    tree.insert(9);
    tree.insert(4);
    tree.insert(12);
    tree.insert(10);
    tree.insert(20);
    tree.insert(3);
    tree.insert(30);
    tree.insert(25);
    tree.insert(1);
    tree.print_tree();
    
    cout << "Max: " << tree.find_max() << "\n";
    cout << "Min: " << tree.find_min() << "\n";
    cout << "Contains: " << tree.contains(2) << "\n";
    std::cout << "Remove 12\n";
    tree.remove(12);
    cout << "New Tree\n";
    tree.print_tree();
    tree.insert(5);
    tree.insert(3);
    cout << "\nNew Tree\n";
    tree.print_tree();
    cout << "Contains: " << tree.contains(3) << "\n";
    tree.remove(4);
    tree.remove(9);
    tree.remove(20);
    tree.remove(3);
    tree.insert(3);
    tree.insert(2);
    cout << "Contains: " << tree.contains(2) << "\n";
    tree.remove(2);
    tree.insert(4);
    tree.remove(4);
    tree.insert(15);
    cout << "Contains: " << tree.contains(15) << "\n";
    tree.remove(15);
    tree.insert(9);
    cout << "Contains: " << tree.contains(9) << "\n";
    tree.remove(9);
    cout << "\nNew Tree\n";
    tree.print_tree();
}

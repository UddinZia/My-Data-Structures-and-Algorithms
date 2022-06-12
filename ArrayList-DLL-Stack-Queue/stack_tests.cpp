#include <iostream>
#include "stack.h"

using std::cout, std::endl;

int main() {
    Stack<int> s1;
    s1.push(1);
    s1.push(2);
    s1.push(3);

    s1.pop();
    cout << s1.top() << endl;

}

#include <iostream>
#include "queue.h"

int main() {
    // TODO(student): test your code
    Queue<int> q1;
    q1.enqueue(1);
    q1.enqueue(2);
    q1.enqueue(3);

    q1.dequeue();

    cout << q1.front() << endl;

}

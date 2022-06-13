#include <iostream>
#include <vector>
#include <deque>
#include <list>

#include "priority_queue.h"

using std::cout, std::endl;

    template <class Comparable>
    struct GreaterThan {
    constexpr bool operator()(const Comparable& lhs, const Comparable& rhs) const {
        return rhs < lhs;
    }
};

int main() {

    
    std::vector<int> vector1 {150,80,40,30,10,70,110,100,20,90,60,50,120,140,130};
    std::vector<int> vector2 {80,40,30,10,70,100,20,90,60,50,120,140,130};

    PriorityQueue<int, std::vector<int>, GreaterThan<int>> queue1(GreaterThan<int>{}, vector1);
    PriorityQueue<int, std::vector<int>, GreaterThan<int>> queue2(queue1);
    PriorityQueue<int, std::vector<int>> queue3(vector2);
    PriorityQueue<int, std::vector<int>> queue4(vector1);

    queue4 = queue3;
    queue4.print_queue();
    
    queue4.push(199);
    queue4.print_queue();

    queue4.pop();
    queue4.print_queue();

    cout << vector2.size() << endl;
    cout << queue4.size() << endl;
    queue4.make_empty();
    cout << queue4.empty() << endl;
   
    

    //queue1.print_queue();
    //queue2.print_queue();

   
    //cout << queue1.top() << endl;

    
    

    


    
    cout << "SELECTION PROBLEM" << endl;
    cout << "make a priority queue from N = 168 elements in O(N) time" << endl;
    std::vector<int> values{509, 887, 53, 739, 491, 307, 727, 223, 919, 263, 983, 7, 809, 353, 659, 769, 173, 431, 619, 139, 2, 3, 181, 23, 283, 617, 463, 757, 89, 541, 997, 743, 907, 13, 337, 349, 523, 857, 97, 827, 661, 67, 373, 59, 11, 277, 379, 19, 941, 607, 367, 101, 457, 929, 599, 971, 967, 647, 71, 991, 211, 467, 881, 137, 311, 673, 197, 179, 859, 239, 233, 631, 449, 281, 499, 269, 877, 421, 419, 613, 593, 383, 937, 569, 487, 839, 479, 461, 683, 653, 227, 61, 107, 113, 947, 191, 103, 313, 733, 151, 257, 73, 821, 547, 521, 691, 83, 823, 443, 31, 5, 643, 131, 389, 571, 163, 271, 601, 359, 199, 853, 29, 167, 557, 157, 193, 977, 37, 41, 773, 347, 709, 251, 331, 829, 503, 409, 719, 397, 241, 47, 641, 787, 863, 109, 587, 17, 751, 229, 911, 811, 317, 563, 701, 797, 953, 293, 149, 439, 127, 883, 577, 79, 433, 43, 761, 401, 677};
    PriorityQueue<int> pq(values);

    cout << "pop k = 42 = O(N / log N) elements in O(k log N) = O(N) time" << endl;
    for (int i = 0; i < 41; i++) { pq.pop(); }
    // ^^^ pops 41, top is would-be 42nd pop vvvvv
    cout << "found k-th smallest element = " << pq.top() << " in O(N + k log N)= O(N) time" << endl;

    cout << endl << "INTERMISSION" << endl;

    cout << "empty the queue in O(1) time" << endl;
    pq.make_empty();
        
    cout << endl << "DISCRETE EVENT SIMULATION" << endl;
    int t = 0;
    size_t busy_start = 0, busy_stop = 0, busy_time = 0, wait_time = 0, cnt = 0, cust_id = 0, next = 7;
    bool busy = false;
    std::list<size_t> line;
    pq.push(t);
    while (!pq.empty()) {
        t = pq.top();
        pq.pop();
        if (t%2) {
            // departure
            cout << "customer departed at time " << t << endl;
            cnt++;
            if (line.empty()) {
                busy = false;
                busy_stop = t;
                busy_time += busy_stop - busy_start;
            } else {
                // next in line
                int arrival_time = line.front();
                line.pop_front();
                wait_time += (t - arrival_time);
                cout << "next customer in line has been waiting " << (t - arrival_time) << " time units" << endl;
                // schedule departure at odd time (t is odd right now), >0 from now
                int service_time = 2*((next+3)%5)+2;
                pq.push(t + service_time);
                next = (next+5)%11;
            }
        } else {
            // arrival
            cout << "customer " << ++cust_id << " arrived at time " << t << endl;
            if (cust_id < 10) {
                // schedule next arrival at even time (t is even right now)
                int interarrival_time = 2*((next+3)%5)+2;
                pq.push(t + interarrival_time);
                next = (next+5)%11;
            }
            if (busy) {
                // wait in line
                line.push_back(t);
                cout << "  server is busy, customer must wait in line, there are " << line.size() << " in line" << endl;
            } else {
                // serve
                busy = true;
                busy_start = t;
                cout << "  service begins immediately" << endl;
                // schedule departure at odd time (t is even right now), >0 from now
                int service_time = 2*((next+3)%5) + 1;
                pq.push(t + service_time);
                next = (next+5)%11;
            }
        }
        
    }
    cout << "end of simulation\n-----------------" << endl;
    cout << "served 10 customers in " << t << " time units" << endl;
    cout << "server was busy for " << busy_time << " total time units" << endl;
    cout << "customers waited " << wait_time << " total time units" << endl;

    // TODO(student): write tests
    
    return 0;
    
}

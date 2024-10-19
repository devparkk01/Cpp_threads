#include<iostream>
#include<thread>
#include<mutex>

using namespace std; 

mutex my_mtx;
static int counter = 0 ;

// a lock guard releases the lock automatically once the function that it is called in goes out of scope!

void increment() {
    for(int i = 0 ; i < 400 ; ++i) {
        // thread acquires the lock 
        lock_guard<mutex> guard(my_mtx);
        counter++;  
    }
}



int main() {

    thread t1(increment);
    thread t2(increment);
    t1.join();
    t2.join();

    cout << "After incrementing with mutex lock guard: "<< counter<< endl ; 
    counter = 0 ;

    return 0 ;
}
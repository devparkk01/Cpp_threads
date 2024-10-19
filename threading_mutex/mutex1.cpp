#include<iostream>
#include<thread>
#include<mutex>

using namespace std; 

mutex my_mtx;
static int counter = 0 ; 

void increment_with_mutex() {

    for(int i = 0 ; i < 400 ; ++i) {
        // thread acquires the lock 
        my_mtx.lock();
        this_thread::sleep_for(chrono::milliseconds(2));
        counter++;  
        my_mtx.unlock();

    }
}

void increment_without_mutex() {
    for(int i = 0 ; i < 400; ++i) {
        this_thread::sleep_for(chrono::milliseconds(2));
        counter++ ;
    }
}

int main() {

    thread t1(increment_with_mutex);
    thread t2(increment_with_mutex);
    t1.join();
    t2.join();

    cout << "with mutex: "<< counter<< endl; 
    counter = 0 ;

    thread t3(increment_without_mutex);
    thread t4(increment_without_mutex);
    t3.join();
    t4.join();

    cout << "without mutex: "<< counter << endl; 

    return 0 ;
}
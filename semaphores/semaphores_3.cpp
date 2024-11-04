/*
let's look into binary_semaphore

*/

#include<iostream>
#include<thread>
#include<semaphore>
#include<vector>

using namespace std; 
#define endl '\n'


binary_semaphore sem{1} ;
// initialises a binary semaphore with the initial value of 1
// 1 means only one thread is allowed at a time

void criticalTask(int id) {
    cout << "Thread " << id << " is waiting to enter critical section."  << endl; 
    sem.acquire(); 
    cout << "Thread " << id << " entered the critial section."  << endl; 
    this_thread::sleep_for(chrono::seconds(1)); // simulating some work
    cout << "Thread " << id << " is leaving the critical section."  << endl; 
    sem.release();
}


int main() {

    vector<thread>threadList; 
    threadList.reserve(10);

    for(int i = 0 ; i < 10 ; ++i) {
        threadList.push_back(thread(criticalTask, i));
        threadList[i].join(); 
    }

    return 0; 

};
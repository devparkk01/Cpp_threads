/* This is about unique_lock 
*/


#include<iostream>
#include<thread>
#include<mutex>


using namespace std; 


mutex m;
int counter = 0 ;


void increment(int id) {
    unique_lock<mutex> lock(m);
    cout << "Thread id " << id << " entered the function " << '\n';
    for(int i = 0 ; i < 5 ; ++i) {
        counter++; 
    }
    cout << "Thread id " << id << " exiting the function " << '\n';
    lock.unlock();
}


int main () {

    vector<thread> t(5);
    for(int i= 0 ; i < 5 ; ++i) {
        t[i] = thread(increment, i);
    }

    for(int i = 0 ; i < 5; ++i) {
        t[i].join(); 
    }

    return 0 ; 

}
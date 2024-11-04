#include<iostream>
#include<atomic>
#include<chrono>
#include<vector>
#include<thread>


using namespace std; 

vector<int>sharedWork ;
atomic<bool> dataReady(false);

void waitingForWork() {
    cout << "Waiting " << endl; 
    while(!dataReady.load()) {
        this_thread::sleep_for(chrono::milliseconds(5));
    }
    sharedWork[1] = 2; 
    cout << "Work done" << endl; 

}

void setDataReady() {
    sharedWork = {1, 0 , 3};
    dataReady = true; 
    cout << "Data prepared" << endl; 
}


int main() {
    thread t1(waitingForWork);
    thread t2(setDataReady);

    t1.join();
    t2.join(); 
    for(auto &x: sharedWork) {
        cout << x << " ";
    }
    return 0; 
}
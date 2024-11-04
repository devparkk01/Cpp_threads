#include<iostream>
#include<thread>
#include<chrono>

using namespace std; 
void print() {
    for(int i = 0 ; i < 10 ; ++i) {
        cout << "print" << endl; 
        this_thread::sleep_for(chrono::milliseconds(20));
    }
}

void read() {
    for(int i = 0 ; i < 30 ; ++i) {
        cout << "read" << endl; 
        this_thread::sleep_for(chrono::milliseconds(20));
    }
}


void write() {
    for(int i = 0 ; i < 50 ; ++i) {
        cout << "write" << endl; 
        this_thread::sleep_for(chrono::milliseconds(20));
    }
}




int main() {

    vector<thread> threadList(3);
    threadList[0] = thread(print);
    threadList[0].join();
    threadList[1] = thread(read);
    threadList[1].join();
    threadList[2] = thread(write);
    threadList[2].join();
    // for(int i = 0 ; i < 3 ; ++i) {
    //     threadList[i].join();
    //     cout << "Join called" << endl; 
    // }
    // t.join();
    // cout << "After join" << endl; 

    return 0; 
}
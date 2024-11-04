#include<iostream>
#include<thread>

using namespace std; 

void print(int count) {
    while(count--) {
        cout << "ThreadList One Printing\n" ; 
    }
}
void read(int count) {
    while(count--) {
        cout << "ThreadList two reading \n";
    }
}

void write(int count) {
    while(count--) {
        cout << "ThreadList three writing \n";
    }
}

int main() {

    vector<thread> threadListOne; 
    threadListOne.reserve(5); // reserve 5 size for this threadList
    for(int i = 0 ; i < 5 ; ++i) {
        threadListOne.push_back(thread(print, 4));
        // threadListOne[i].join();  Do not put the join while creating threads. They won't be actually doing multithreading 
    }

    for(int i = 0 ;  i < 5 ; ++i) {
        threadListOne[i].join();
    }

    vector<thread>threadListTwo(5);
    for(int i = 0 ; i < 5; ++i) {
        threadListTwo[i] = thread(read, 4);
        // threadListTwo[i].join(); Do not put the join while creating threads. They won't be actually doing multithreading 
    }
    for(int i = 0 ;  i < 5 ; ++i) {
        threadListTwo[i].join();
    }
    vector<thread>threadListThree;
    threadListThree.reserve(5);

    for(int i = 0 ; i < 5;  ++i) {
        threadListThree.emplace_back(write, 5); 
        // threadListThree[i].join();  Do not put the join while creating threads. They won't be actually doing multithreading 
    }

    for(int i = 0 ;  i < 5 ; ++i) {
        threadListThree[i].join();
    }

    return 0 ;
}
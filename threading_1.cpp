#include <thread>
#include <iostream>
using namespace std; 

void print() {
    cout << "Printing " << endl; 
}

void counting(int a) {
    for(int i = 0 ; i < a; ++i) {
        cout << i << endl;
        this_thread::sleep_for(chrono::seconds(1)) ;
    }
    cout << "finished executing thread with id: " << this_thread::get_id() << endl;
}



int main() {
    cout << thread::hardware_concurrency() << endl; 

    thread t1(counting, 2);
    thread t2(counting, 2);

    // wait for threads to finish executing 
    t1.join();
    t2.join();



    return 0; 
}
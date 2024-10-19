/*
use this command to run this file 
g++ -std=c++20 semaphores_2.cpp -o out
./out

*/

#include <iostream>
#include <thread>
#include <semaphore>  // C++20 semaphore

using namespace std; 

#define MAX_CONCURRENT_THREADS 2
#define INITIAL_VALUE 2

counting_semaphore<MAX_CONCURRENT_THREADS> semaphore(INITIAL_VALUE);  // Allows up to 2 threads to work simultaneously

void worker(int id) {
    semaphore.acquire();  // Acquire semaphore

    // Critical section
    cout << "Thread " << id << " is working...\n";
    this_thread::sleep_for(chrono::seconds(1));

    semaphore.release();  // Release semaphore
}

int main() {
    vector<thread> threads;
    for (int i = 0; i < 5; ++i) {
        threads.push_back(thread(worker, i));
    }

    for (auto& t : threads) {
        t.join();
    }

    return 0;
}

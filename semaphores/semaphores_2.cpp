/* Newer version of semaphore
Provided with c++20 

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

/*
counting_semaphore<3> semaphore(2);  
Maximum counter value 3 (that means maximum 3 threads can access simultaneously), initial count of 2
counting_semaphore<5> semaphore(3); 
Maximum counter value 3 (that means maximum 3 threads can access simultaneously), initial count of 2
*/


counting_semaphore<MAX_CONCURRENT_THREADS> semaphore(INITIAL_VALUE);  // Allows up to 2 threads to work simultaneously


void worker(int id) {
    semaphore.acquire();  // Acquire semaphore -> wait until the count is greater than 0, then decrement the counter 

    // Critical section
    cout << "Thread " << id << " is working...\n";
    this_thread::sleep_for(chrono::seconds(1));

    semaphore.release();  // Release semaphore -> increments the counter
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

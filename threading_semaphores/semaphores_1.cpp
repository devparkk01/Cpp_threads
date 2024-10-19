#include<iostream>
#include<thread>
#include<semaphore.h>

#define MAX_CONCURRENT_THREADS  2 

sem_t semaphore; // Declare a posix semaphore

using namespace std;

void worker(int id){

    sem_wait(&semaphore);  // Wait until semaphore is available (decrements the counter)
    
    // Critical section (only a limited number of threads can access this)
    cout << "Thread " << id << " is working...\n";
    this_thread::sleep_for(chrono::seconds(1));

    sem_post(&semaphore);  // Release the semaphore (increments the counter)
}

int main() {
    sem_init(&semaphore, 0 , MAX_CONCURRENT_THREADS); // Initialize the semaphore with a value of 2

    vector<thread>threads; threads.reserve(5);
    
    for(int i = 0 ; i < 5; ++i) {
        threads.push_back(thread(worker, i));
    }
    for(int i = 0 ; i < 5; ++i) {
        threads[i].join(); // Wait for all threads to finish
    }

    sem_destroy(&semaphore); // Destroy the semaphore

}
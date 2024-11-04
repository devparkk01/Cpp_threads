#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

using namespace std; 

mutex mtx;
condition_variable cv;
bool ready = false;

void printId(int id) {
    unique_lock<mutex> lock(mtx); // mutex is needed for condition variable 
    // Wait until ready becomes true
    cv.wait(lock, [] { return ready; });
    // After being notified, proceed
    cout << "Thread " << id << '\n';
}

void go() {
    ready = true;  // set ready to true 
    cout << "Go signal sent, notifying all threads.\n";
    // Notify all waiting threads
    cv.notify_all();
}

int main() {
    thread threads[5];
    
    // Spawn 5 threads
    for (int i = 0; i < 5; ++i){
        threads[i] = thread(printId, i);
    }

    this_thread::sleep_for(chrono::seconds(1));
    go(); // Signal all threads to proceed

    // Join all threads
    for (auto& th : threads) th.join();

    return 0;
}

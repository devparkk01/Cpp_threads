/*
There are multiple users calling a method reg_cb at different intances of time, as shown below. 
Simultaneously, there is an event happening. All the user requests that were made during the execution of the 
event should wait till the event completes and then execute the reg_cb method.
 Once the event is finished, the user requests to the reg_cb method can be executed immediatly. 
 Implement how to handle the given scenario.

*/

#include<iostream>
#include<thread>
#include<mutex>
#include<condition_variable>
#include<vector>
#include<chrono>

using namespace std; 

class EventSynchronizer {
    bool isEventRunning ; 
    mutex mtx; 
    condition_variable cv; 

    public:
    EventSynchronizer() {
        isEventRunning = false; 
    }

    void reg_cb(int userId) {
        unique_lock<mutex> lock(mtx);
        cv.wait(lock, [this]() {
            return ( !this->isEventRunning);
        });

        lock.unlock();  // Release the lock explicitly to allow other threads to proceed

        // Simulate task execution
        cout << "userid " << userId << " is executing reg_cb method...\n"; 
        this_thread::sleep_for(chrono::milliseconds(200));
        cout << "userid " << userId << " has executed reg_cb method...\n"; 

    }


    void runEvent() {
        {
            unique_lock<mutex> lock(mtx);
            isEventRunning = true; 
        } // lock releases automatically when it goes out of scope

        // do some work 
        cout << "Event started... \n" ; 
        this_thread::sleep_for(chrono::seconds(5));
        cout << "Even finished... \n";

        {
            unique_lock<mutex> lock(mtx);
            isEventRunning = false; 
        } // lock releases automatically when it goes out of scope

        cv.notify_all();  // notify all waiting threads 
    }
};

int main () {

    EventSynchronizer synchronizer; 

    thread eventThread([&synchronizer]() {
        synchronizer.runEvent(); 
    });
    
    vector<thread> users(5);

    for(int i = 0 ; i < 5 ; ++i) {
        users[i] = thread([&synchronizer, i]() { 
            synchronizer.reg_cb(i);
        });
    }


    eventThread.join();

    for(int i = 0 ; i < 5 ; ++i) {
        users[i].join();
    }

    cout << "Execution finished \n";

    return 0 ; 
}
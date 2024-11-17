#include <iostream>
#include <condition_variable>
#include <mutex>
#include <thread>

using namespace std; 

mutex mtx;
condition_variable cv;

bool dataReady{false};

void doTheWork(){
    cout << "Processing shared data.\n" ;
    this_thread::sleep_for(chrono::seconds(3));
}

void waitingForWork(){
    cout << "Worker: Waiting for work.\n" ;
    unique_lock<mutex> lck(mtx);
    cv.wait(lck, []{ return dataReady; });
    doTheWork();
    cout << "Work done.\n" ;
}

void setDataReady(){
    {
        unique_lock<mutex> lck(mtx);
        dataReady = true;
        cout << "Sender: Data is ready.\n" ;
    }
    cv.notify_one();
}

int main(){

    thread t1(waitingForWork);
    thread t2(setDataReady);
    t1.join();
    t2.join();

    return 0; 
}
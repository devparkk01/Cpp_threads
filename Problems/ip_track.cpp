#include<iostream>
#include<thread>
#include<chrono>

using namespace std; 


class Counter{
    public:
    long time_window; 
    long start_time; 
    int count; 

    Counter(long time_window, long start_time) {
        this->time_window = time_window; 
        this->start_time = start_time; 
        count = 0 ; 
    }

    int getCount() {
        if ( windowExpired()) {
            count = 0; 
        }
        return count; 
    }

    void setCount() {
        count = 0 ; 
    }

    void incrementCount() {
        if (windowExpired()) {
            count = 1 ;
        }  else {
            count++;
        }
    }

    bool windowExpired() {
        long current_time = chrono::system_clock::now().time_since_epoch().count();
        if ( current_time - start_time  > time_window) {
            start_time = chrono::system_clock::now().time_since_epoch().count() ;
            return true; 
        }
        return false; 
    }

};


int main(){

    long start_time = chrono::system_clock::now().time_since_epoch().count(); 
    long time_window =  chrono::milliseconds(100).count();
    Counter c = Counter(start_time, time_window);
    c.incrementCount();
    c.incrementCount();
    cout << c.getCount() << endl;
    c.incrementCount();
    cout << c.getCount() << endl;
    c.incrementCount();
    cout << c.getCount() << endl;
    this_thread::sleep_for(chrono::milliseconds(100));
    cout<< c.getCount() << endl; 
    c.incrementCount();
    cout<< c.getCount() << endl; 


    return 0 ; 
}